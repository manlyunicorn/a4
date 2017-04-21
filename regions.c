#include "regions.h"
# include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifndef NAME_SIZE
#define NAME_SIZE 1024
#endif
typedef unsigned char uchar;
typedef unsigned long ulong;

typedef struct BLOCKNODE{
    r_size_t size;
    unsigned long offset;
    struct BLOCKNODE *next;
    r_size_t spaceAfter;
}BlockNode, *BlockNodePtr;

typedef struct NODE{
    BlockNodePtr head;
    r_size_t size;
    r_size_t space;
    char * name;
    uchar *buffer;
    struct NODE *next;
}Node, *NodePtr;

NodePtr head = NULL;
NodePtr chosen = NULL;
int count = 0;


Boolean rinit(const char *region_name, r_size_t region_size){
    chosen->space = chosen->space-roundedSize;
    result = chosen->buffer;

    return result;
}
r_size_t rsize(void *block_ptr){
    void * ptr = NULL;
    if(chosen!=NULL){
            //....
    }
    return 0;
}
Boolean rfree(void *block_ptr){
    void * ptr = NULL;
    if(chosen!=NULL){
        BlockNodePtr temp = chosen->head;
        BlockNodePtr tempB = NULL;
        while(temp!=NULL){
            if(ptr==block_ptr){
                if(tempB!=NULL){
                    return true;
                }
                else{
                        //...
                }

            }
            tempB = temp;
            temp = temp->next;
        }
    }
}
void rdestroy(const char *region_name){
    NodePtr tempB = NULL;
    NodePtr temp = head;
    Boolean finished = false;
    while(temp!=NULL&&!finished){
            //...
    }
}
void rdump(){
    printf("Summary:\n");
    NodePtr temp = head;
    if(temp==NULL){
        printf("NULL\n");
    }
    else{
            //...
    }
}
