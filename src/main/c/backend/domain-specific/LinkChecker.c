#include "LinkChecker.h"
¨
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


void storeHeader(Text * text, HeaderList * headerList){
    HeaderList * newHeader = calloc(1,sizeof(HeaderList));
    newHeader->header = text->string;
    newHeader->next = headerList;
    headerList = newHeader;
}

void storeLink(Text * text, LinkList * linkList){
    LinkList * newLink = calloc(1,sizeof(LinkList));
    newLink->link = text->link->link;
    newLink->next = linkList;
    linkList = newLink;
}

bool checkLinks(HeaderList * headerList, LinkList * linkList){
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

//primero guardo todos los headers y los links
//luego recorro la lista de links chequeando que exista dentro de la lista de headers
bool checkProgram(MasterBlock * masterBlock) {
    HeaderList * headerList = calloc(1,sizeof(HeaderList));
    LinkList * linkList = calloc(1,sizeof(LinkList));
    bool out = false;
    if(masterBlock->type == MASTER_BLOCK_LIST){
        while(masterBlock->second != NULL){
            if(masterBlock->type == MASTER_BLOCK_LIST){
                if(masterBlock->second->type == H1){ //SOLO NOS GUARDAMOS LOS H1 O LOS HEADER MENORES TAMBIEN? SOLUCION SI GUARDAMOS LOS MENORES TAMBIEN ES MODULARIZAR EL HEADER A SOLO 1 H Y PASAR POR PARAMETRO EL NUMERO DE HEADER
                    if(headerList->header == 0){
                        headerList->header = masterBlock->second->text;
                    }else{
                        storeHeader(masterBlock->second->text, headerList);
                    }
                }
                else if(masterBlock->second->type == LINK){
                    storeLink(masterBlock->second->text, linkList); 
                }
            }
        }
        out = checkLinks(headerList, linkList);
    }
    return out;
}
