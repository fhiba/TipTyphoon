#include "LinkChecker.h"

static Logger * _logger = NULL;

void initializeCheckerModule() {
	_logger = createLogger("LinkChecker");
}

void shutdownCheckerModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

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

void checkBlock(Block * block);
void lookForLinks(Block * block);
void storeHeader(char * text);
void storeLink(Text * text);
boolean checkLinks();
void freeHeaders();
void freeLinks();
char * processText(Text * text);
void lookForLinks(Block * block);
void lookForLinksInText(Text * text);
HeaderList * headerList;
LinkList * linkList;


//primero guardo todos los headers y los links
//luego recorro la lista de links chequeando que exista dentro de la lista de headers
boolean checkProgram(MasterBlock * masterBlock) {
    headerList = calloc(1,sizeof(HeaderList));
    linkList = calloc(1,sizeof(LinkList));
    boolean out = false;
    
    logDebugging(_logger, "Checking program for valid links...");
    while(masterBlock != NULL && masterBlock->type == MASTER_BLOCK_LIST) {
        logDebugging(_logger, "Searching in the block list...");
        checkBlock(masterBlock->second);
        masterBlock = masterBlock->first;
    }
    if(masterBlock != NULL) {
        checkBlock(masterBlock->block);
    }
    logDebugging(_logger, "Finished checking blocks...");
    logDebugging(_logger, "ESTE ES MI HEADER %s...",headerList->header);
    
    out = checkLinks();
    freeHeaders(headerList);
    freeLinks(linkList);
    logDebugging(_logger, "Finished checking program...");
    return out;
}

void storeHeader(char * text){
    HeaderList * newHeader = calloc(1,sizeof(HeaderList));
    newHeader->header = text;
    newHeader->next = headerList;
    headerList = newHeader;
    logDebugging(_logger, "Stored Header %s...",headerList->header);
}

char* removeHash(char* str) {
    if (str[0] == '#') {
        return str + 1;
    }
    return str;
}

void storeLink(Text * text){
    if(text->link->link[0] != '#'){
        return;
    }
    LinkList * newLink = calloc(1,sizeof(LinkList));
    newLink->link = removeHash(text->link->link);
    newLink->next = linkList;
    linkList = newLink;
    logDebugging(_logger, "Stored Link...");
}

boolean checkLinks(){
    LinkList * currentLink = linkList;
    HeaderList * currentHeader = headerList;
    logDebugging(_logger, "Checking Links...");
    if(currentHeader->header == NULL){
        logDebugging(_logger, "HeaderList is empty %s...",currentHeader->header);
        return false;
    }
    boolean found = false;
    while(currentLink->next != NULL){
        logDebugging(_logger, "Checking link %s...",currentLink->link);
        while(currentHeader->next != NULL){
            logDebugging(_logger, "Checking header %s...",currentHeader->header);
            if(strcmp(currentLink->link, currentHeader->header) == 0){ //si en la lista lo encuentra, entonces dejo de recorrer los headers y paso al siguiente link
                logDebugging(_logger, "Found header for link...");
                found = true;
                break;
            }
            currentHeader = currentHeader->next;
        }
        if(!found){
            logDebugging(_logger, "Link not found in headers...");
            return false;
        }
        found = false;
        currentLink = currentLink->next;
        currentHeader = headerList; //reseteo la lista de headers porque puede estar antes.
    }
    logDebugging(_logger, "Finished checking links...");
    return true;
}

void freeHeaders(HeaderList * headers){
    logDebugging(_logger, "Freeing Headers...");
    if(headers != NULL){
        freeHeaders(headers->next);
        free(headers->header);
        free(headers);
    }
}

void freeLinks(LinkList * links){
    logDebugging(_logger, "Freeing Links...");
    if(links != NULL){
        freeLinks(links->next);
        free(links);
    }
}


void lookForLinksInText(Text * text) {
    switch(text->type) {
        case TEXT:
            break;
	    case UNION:
            lookForLinksInText(text->left);
            lookForLinksInText(text->right);
            break;
	    case BOLD:
	    case ITALIC:
	    case CODE:
            lookForLinksInText(text->child);
            break;
        case LINK:
            logDebugging(_logger, "Found Link...");
            storeLink(text);
            break;
    }
}

void lookForLinksInThirdTList(ThirdTList *list) {
    if(list == NULL) {
        return;
    }
    switch (list->type)
    {
    case UL:
        lookForLinksInThirdTNode(list->unordered);
    case OL:
        lookForLinksInThirdTNode(list->ordered);
        break;
    }
}


void lookForLinksInThirdTItem(void * item) {
    if(item == NULL) {
        return;
    }

    lookForLinksInText(((ThirdTItemOrdered*)item)->text);
}

void lookForLinksInThirdTNode(void * node) {
    if(node == NULL) {
        return;
    }
    switch (((ThirdTNodeOrdered*)node)->type)
    {
    case NODE:
        lookForLinksInThirdTNode(((ThirdTNodeOrdered*)node)->node);
        lookForLinksInThirdTItem(((ThirdTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        lookForLinksInThirdTItem(((ThirdTNodeOrdered*)node)->item);
        break;
    default:
        logCritical(_logger, "Invalid ThirdTNode type");
        break;
    }
}

void lookForLinksInSecondTItem(void * item) {
    if(item == NULL) {
        return;
    }
    switch (((SecondTItemOrdered*)item)->type)
    {
    case ITEM:
        lookForLinksInText(((SecondTItemOrdered*)item)->text);
        break;
    case LIST_ITEM:
        lookForLinksInThirdTList(((SecondTItemOrdered*)item)->list);
        break;
    default:
        logCritical(_logger, "Invalid FirstTItem type");
        break;
    }

}


void lookForLinksInSecondTNode(void * node) {
    if(node == NULL) {
        return;
    }
    switch (((SecondTNodeOrdered*)node)->type)
    {
    case NODE:
        lookForLinksInSecondTNode(((SecondTNodeOrdered*)node)->node);
        lookForLinksInSecondTItem(((SecondTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        lookForLinksInSecondTItem(((SecondTNodeOrdered*)node)->item);
        break;
    default:
        logCritical(_logger, "Invalid SecondTNode type");
        break;
    }
}


void lookForLinksInSecondTList(SecondTList * list) {
    if(list == NULL) {
        return;
    }
    switch (list->type)
    {
    case UL:
        lookForLinksInSecondTNode(list->unordered);
    case OL:
        lookForLinksInSecondTNode(list->ordered);
        break;
    }
}

void lookForLinksInFirstTItem(void * item) {
    if(item == NULL) {
        return;
    }
    switch (((FirstTItemOrdered*)item)->type)
    {
    case ITEM:
        lookForLinksInText(((FirstTItemOrdered*)item)->text);
        break;
    case LIST_ITEM:
        lookForLinksInSecondTList(((FirstTItemOrdered*)item)->list);
        break;
    default:
        logCritical(_logger, "Invalid FirstTItem type");
        break;
    }

}

void lookForLinksInFirstTNode(void * node) {
    if(node == NULL) {
        return;
    }
    switch (((FirstTNodeOrdered*)node)->type)
    {
    case NODE:
        lookForLinksInFirstTNode(((FirstTNodeOrdered*)node)->node);
        lookForLinksInFirstTierItem(((FirstTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        lookForLinksInFirstTierItem(((FirstTNodeOrdered*)node)->item);
        break;
    default:
        logCritical(_logger, "Invalid FirstTNode type");
        break;
    }
}


void lookForLinksInList(FirstTList * list) {
    if(list == NULL) {
        return;
    }
    switch (list->type)
    {
        case UL:
            lookForLinksInFirstTNode(list->unordered);
        case OL:
            lookForLinksInFirstTNode(list->ordered);
            break;
    }
}

void lookForLinks(Block * block) {
    switch (block->type)
    {
    case BQ:
    case SIMPLE:
        lookForLinksInText(block->text);
        break;
    case LIST:
        lookForLinksInList(block->list);
        break;
    }
}


void checkBlock(Block * block) {
    switch(block->type) {
        case H1:
        case H2:
        case H3:
        case H4:
        case H5:
        case H6:
            logDebugging(_logger, "Processing Header...");
            storeHeader(processText(block->text));
            break;
        case STYLING:
            break;
        default:
            logDebugging(_logger, "Looking for link in other type blocks...");
            lookForLinks(block);
            break;
    }
}

void concatStr(char * dest, char * src, int len) {
    while(*src) {
        dest[len++] = tolower(*src++);
    }
    dest[len] = '\0';
}

void concatenateRec(Text * text, char * out, int * len, int * allocated) {
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
            concatenateRec(text->left, out, len, allocated);
            while(*len + 1 > *allocated) {
                out = realloc(out, *allocated + BLOCK_SIZE);
                *allocated += BLOCK_SIZE;
            }
            concatStr(out, "-", *len);
            *len += 1;
            concatenateRec(text->right, out, len, allocated);
            break;
        case BOLD:
        case ITALIC:
        case CODE:
            concatenateRec(text->child, out, len, allocated);
            break;
        case LINK:
            storeLink(text);
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

char * processText(Text * text) {
    logDebugging(_logger, "Started Processing text...");
    char * out = calloc(BLOCK_SIZE, sizeof(char));
    int allocated = 0;
    int len = 0;
    concatenateRec(text, out, &len, &allocated);
    logDebugging(_logger, "Finished concatenating text...");
    logDebugging(_logger, "out = %s",out);
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

