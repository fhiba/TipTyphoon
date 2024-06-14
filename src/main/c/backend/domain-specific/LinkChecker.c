#include "LinkChecker.h"

typedef struct HeaderList HeaderList;
typedef struct LinkList LinkList;

struct HeaderList{
    char * header;
    HeaderList * next;
};

struct LinkList{
    char * link;
    LinkList * next;
};

void checkBlock(Block * block, HeaderList * headers, LinkList * list);
void lookForLinks(Block * block, LinkList * list);
void storeHeader(char * text, HeaderList * headerList);
void storeLink(Text * text, LinkList * linkList);
boolean checkLinks(HeaderList * headerList, LinkList * linkList);
void freeHeaders(HeaderList * headerList);
void freeLinks(LinkList * linkList);
char * processText(Text * text, LinkList * list);
void lookForLinks(Block * block, LinkList * list);
void lookForLinksInText(Text * text,LinkList * list);


//primero guardo todos los headers y los links
//luego recorro la lista de links chequeando que exista dentro de la lista de headers
boolean checkProgram(MasterBlock * masterBlock) {
    HeaderList * headerList = calloc(1,sizeof(HeaderList));
    LinkList * linkList = calloc(1,sizeof(LinkList));
    boolean out = false;
    
    
    while(masterBlock != NULL && masterBlock->type == MASTER_BLOCK_LIST) {
        checkBlock(masterBlock->second, headerList, linkList);
        masterBlock = masterBlock->first;
    }
    if(masterBlock != NULL) {
        checkBlock(masterBlock->block, headerList, linkList);
    }
    
    out = checkLinks(headerList, linkList);
    freeHeaders(headerList);
    freeLinks(linkList);
    return out;
}





void storeHeader(char * text, HeaderList * headerList){
    HeaderList * newHeader = calloc(1,sizeof(HeaderList));
    newHeader->header = text;
    newHeader->next = headerList;
    headerList = newHeader;
}

void storeLink(Text * text, LinkList * linkList){
    if(text->link->link[0] != '#')
        return;
    LinkList * newLink = calloc(1,sizeof(LinkList));
    newLink->link = text->link->link;
    newLink->next = linkList;
    linkList = newLink;
}

boolean checkLinks(HeaderList * headerList, LinkList * linkList){
    LinkList * currentLink = linkList;
    HeaderList * currentHeader = headerList;
    while(currentLink != NULL){
        while(currentHeader != NULL){
            if(strcmp(currentLink->link, currentHeader->header) == 0){ //si en la lista lo encuentra, entonces dejo de recorrer los headers y paso al siguiente link
                break;
            }
            if(currentHeader->next == NULL){ //si llego al final de la lista de headers y no encontro el link, entonces retorno false
                return false;
            }
            currentHeader = currentHeader->next;
        }
        currentLink = currentLink->next;
        currentHeader = headerList; //reseteo la lista de headers porque puede estar antes.
    }
    return true;
}

void freeHeaders(HeaderList * headerList){
    if(headerList != NULL){
        freeHeaders(headerList->next);
        free(headerList);
    }
}

void freeLinks(LinkList * linkList){
    if(linkList != NULL){
        freeLinks(linkList->next);
        free(linkList);
    }
}


void lookForLinksInText(Text * text,LinkList * list) {
    switch(text->type) {
        case TEXT:
            break;
	    case UNION:
            lookForLinksInText(text->left, list);
            lookForLinksInText(text->right, list);
            break;
	    case BOLD:
	    case ITALIC:
	    case CODE:
            lookForLinksInText(text->child, list);
            break;
        case LINK:
            storeLink(text, list);
            break;
    }
}

void lookForLinks(Block * block, LinkList * list) {
    switch (block->type)
    {
    case BQ:
    case SIMPLE:
        lookForLinksInText(block->text, list);
        break;
    case LIST:
        lookForLinksInText(block->list->content,list);
        break;
    }
}


void checkBlock(Block * block, HeaderList * headers, LinkList * links) {
    switch(block->type) {
        case H1:
        case H2:
        case H3:
        case H4:
        case H5:
        case H6:
            storeHeader(processText(block->text, links), headers);
            break;
        default:
            break;
    }
    if(block->type != STYLING) {
        lookForLinks(block, links);
    }
}

void concatStr(char * dest, char * src, int len) {
    while(*src) {
        dest[len++] = tolower(*src++);
    }
    dest[len] = '\0';
}

void concatenateRec(Text * text, char * out, int * len, int * allocated, LinkList * list) {
    if(text == NULL) {
        return;
    }
    int textLen;
    switch(text->type) {
        case TEXT:
            textLen = strlen(text->string);
            while(*len + textLen > *allocated) {
                out = realloc(out, *allocated + BLOCK_SIZE);
                *allocated += BLOCK_SIZE;
            }
            concatStr(out, text->string, *len);
            *len += textLen;
            break;
        case UNION:
            concatenateRec(text->left, out, len, allocated,  list);
            while(*len + 1 > *allocated) {
                out = realloc(out, *allocated + BLOCK_SIZE);
                *allocated += BLOCK_SIZE;
            }
            concatStr(out, "-", *len);
            *len += 1;
            concatenateRec(text->right, out, len, allocated, list);
            break;
        case BOLD:
        case ITALIC:
        case CODE:
            concatenateRec(text->child, out, len, allocated, list);
            break;
        case LINK:
            storeLink(text, list);
            char * string = text->link->string;
            textLen = strlen(string);
            while(*len + textLen > *allocated) {
                out = realloc(out, *allocated + BLOCK_SIZE);
                *allocated += BLOCK_SIZE;
            }
            concatStr(out, string, *len);
            *len += textLen;
            break;
    }
}

char * processText(Text * text, LinkList * list) {
    char * out = calloc(BLOCK_SIZE, sizeof(char));
    int allocated = 0;
    int len = 0;
    concatenateRec(text, out, &len, &allocated, list);
    out = realloc(out, len + 1);
    out[len] = '\0';
    return out;
}

/*
* MI BLOQUE TENGO QUE VER SI ES LIST O NO
* Si es list tengo que ver que pasa adentro
* Si es block solo veo que hay adentro
* luego si es un link tengo q guardarlo
* si es un header tengo que procesarlo y guardarlo
*
*/

