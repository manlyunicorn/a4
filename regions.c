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

typedef struct BLOCKNODE {
	r_size_t size;
	unsigned long offset;
	struct BLOCKNODE *next;
	r_size_t spaceAfter;
}BlockNode, *BlockNodePtr;

typedef struct NODE {
	BlockNodePtr head;
	r_size_t size;
	r_size_t space;
	char * name;
	uchar *buffer;
	struct NODE *next;
	int counter;
}Node, *NodePtr;

NodePtr head = NULL;
NodePtr chosen = NULL;
int count = 0;


Boolean rinit(const char *region_name, r_size_t region_size) {
	if (region_size <= 0) {
		return false;
	}
	int i = 0;
	NodePtr test = head;
	for (i = 0; i<count; i++) {
		if (strcmp(region_name, test->name) == 0) {
			return false;
		}
	}
	NodePtr newNode = (NodePtr)malloc(sizeof(Node));
	uchar temp[(r_size_t)(ceil((double)region_size / 8.0) * 8)];
	newNode->buffer = temp;
	newNode->counter = 0;
	newNode->head = NULL;
	newNode->size = (r_size_t)(ceil((double)region_size / 8.0) * 8);
	newNode->space = newNode->size;
	newNode->buffer = (uchar *)malloc(newNode->size);
	char *tempCharArray = (char *)malloc(NAME_SIZE);
	strcpy(tempCharArray, region_name);
	newNode->name = tempCharArray;

	if (count == 0) {
		head = newNode;
	}
	else {
		Node *temp = head;
		int num = 0;
		while (temp->next != NULL&&num<count - 1) {
			temp = temp->next;
			num++;
		}
		temp->next = newNode;
	}
	count++;
	chosen = newNode;
	return true;
}
Boolean rchoose(const char *region_name) {
	int i = 0;
	NodePtr test = head;
	for (i = 0; i<count; i++) {

		if ((strcmp(region_name, test->name) == 0)) {
			chosen = test;
			return true;
		}
		test = test->next;
	}
	return false;
}
const char *rchosen() {
	if (chosen != NULL) {
		return chosen->name;
	}
	else {
		return NULL;
	}
}
void *ralloc(r_size_t block_size) {
	void * result = NULL;
	r_size_t roundedSize = (r_size_t)(ceil((double)block_size / 8) * 8);
	if (chosen->space<block_size) {
		return NULL;
	}
	if (block_size == 0 || chosen == NULL) {
		return NULL;
	}
	if (chosen->size == chosen->space) {
		BlockNodePtr newNode = (BlockNodePtr)malloc(sizeof(BlockNode));
		newNode->offset = 0;
		newNode->next = NULL;
		newNode->size = roundedSize;
		newNode->spaceAfter = chosen->space - newNode->offset - newNode->size;
		chosen->head = newNode;
		chosen->space = chosen->space - roundedSize;
		result = chosen->buffer;

	}
	else {
		Boolean completed = false;
		BlockNodePtr temp = chosen->head;
		if (temp->offset >= roundedSize) {
			BlockNodePtr newNode = (BlockNodePtr)malloc(sizeof(BlockNode));
			newNode->size = roundedSize;
			newNode->spaceAfter = temp->offset - roundedSize;
			newNode->next = temp;
			result = chosen->buffer + newNode->offset;
		}
		while (temp != NULL && !completed) {

			if (temp->spaceAfter >= roundedSize) {
				completed = true;
				chosen->counter++;
				chosen->space = chosen->space - block_size;
				BlockNodePtr newNode = (BlockNodePtr)malloc(sizeof(BlockNode));
				newNode->size = roundedSize;
				newNode->offset = temp->offset + temp->size;
				temp->spaceAfter = 0;
				if (temp->next == NULL) {
					newNode->next = NULL;
					newNode->spaceAfter = chosen->size - newNode->offset - newNode->size;
				}
				else {
					newNode->next = temp->next;
					newNode->spaceAfter = temp->next->offset - newNode->offset - newNode->size;

				}
				temp->next = newNode;
				result = chosen->buffer + newNode->offset;
			}
			temp = temp->next;
		}
	}

	return result;
}
r_size_t rsize(void *block_ptr) {
	void * ptr = NULL;
	if (chosen != NULL) {
		BlockNodePtr temp = chosen->head;
		while (temp != NULL) {
			ptr = NULL;
			ptr = chosen->buffer + temp->offset;
			if (ptr == block_ptr) {
				return temp->size;
			}
			temp = temp->next;
		}
	}
	return 0;
}
Boolean rfree(void *block_ptr) {

	void * ptr = NULL;
	if (chosen != NULL) {
		BlockNodePtr temp = chosen->head;
		BlockNodePtr tempB = NULL;
		while (temp != NULL) {
			ptr = NULL;
			ptr = chosen->buffer + temp->offset;
			if (ptr == block_ptr) {
				if (tempB != NULL) {
					tempB->spaceAfter = tempB->spaceAfter + temp->size;
					tempB->next = temp->next;
					chosen->space = chosen->space + temp->size;
					if (temp->next == NULL) {
					}
					chosen->space = chosen->space + temp->size;
					free(temp);
					return true;
				}
				else {
					chosen->head = temp->next;
					if (temp->next == NULL) {
					}
					chosen->space = chosen->space + temp->size;
					free(temp);
					return true;
				}

			}
			tempB = temp;
			temp = temp->next;
		}
	}
	return false;
}
void rdestroy(const char *region_name) {
	NodePtr tempB = NULL;
	NodePtr temp = head;
	Boolean completed = false;
	while (temp != NULL && !completed) {
		if (strcmp(region_name, temp->name) == 0) {
			count--;
			if (tempB != NULL) {
				tempB->next = temp->next;
			}
			else {
				head = temp->next;
			}
			free(temp->name);
			free(temp->buffer);
			BlockNodePtr temp2 = temp->head;
			BlockNodePtr temp2N = NULL;
			if (temp2 != NULL) {
				temp2N = temp->head->next;
			}
			while (temp2 != NULL) {
				free(temp2);
				temp2 = temp2N;
				if (temp2N != NULL) {
					temp2N = temp2N->next;
				}
			}
			completed = true;
			free(temp);
		}
		else {
			tempB = temp;
			temp = temp->next;
		}
	}
}
void rdump() {
	printf("Summary:\n");
	NodePtr temp = head;
	if (temp == NULL) {
		printf("NULL\n");
	}
	else {
		int i = 0;
		for (i = 0; i<count; i++) {
			printf("\nRegion: %s\tsize: %d\tfree space: %d percent\n", temp->name, temp->size, temp->space * 100 / temp->size);
			BlockNodePtr tempBlock = temp->head;
			int counter = 0;
			while (tempBlock != NULL&&counter<temp->counter) {
				printf("Block Number: %d\t size: %d\n", counter, tempBlock->size);
				counter++;
				tempBlock = tempBlock->next;
			}
			temp = temp->next;
		}
	}
}
