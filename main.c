#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"


int compareInteger(void * num1, void * num2) {
    
    int * x = (int *)num1;
    int * y = (int *)num2;
    if (*x < *y) {
        return -1;
    } else if (*x == *y) {
        return 0;
    }
    
    return 1;
}

int compareStrings() {
    
    return 0;
}

int compareChars() {
    
    return 0;
}

int compareFloats(void * num1, void * num2) {
    
    float * x = (float *)num1;
    float * y = (float *)num2;
    
    if (*x < *y) {
        return -1;
    } else if (*x == *y) {
        return 0;
    }
    
    return 1;
}

int compareDoubles(void * num1, void * num2) {
    
    double * x = (double *)num1;
    double * y = (double *)num2;
    
    if (*x < *y) {
        return -1;
    } else if (*x == *y) {
        return 0;
    }
    
    return 1;
}

void destroyList(void *n) {
    
    Node *node = (Node*)n;
    if (node->next == NULL) {
        free(node);
        return;
    }

    destroyList(node->next);
    free(node);
    return;
    
}

void destroyNode(void *n) {
    
    Node * no = (Node*)n;
    
    printf("Removing Node: %d\n", *(int*)no->data);
    
    free(no);
    
    return;
}

void printNodes(SortedListIteratorPtr iter) {
    
    while (iter->node != NULL) {
        
        printf("Data: %d\t", *(int*)iter->node->data);
        iter->node = iter->node->next;        
    }
    printf("\n");
    
}

int main(int argc, char **argv) {
    
    int a = 5;
    int b = 7;
    int c = 6;
    int z = 7;
    
    void *d = &a;
    void *e = &b;
    void *f = &c;
    void *h = &z;
    
    int (*integer)() = compareInteger;
    void (*destroy)(void *) = destroyNode;

    SortedListPtr sl = SLCreate(integer, destroy);
    
    int x = SLInsert(sl, d);
    x = SLInsert(sl, e);
    x = SLInsert(sl, h);
    x = SLInsert(sl, f);
    
    Node * temp = sl->head;
    SortedListIteratorPtr iterator = SLCreateIterator(sl);
    
    printNodes(iterator);  
    int y = SLRemove(sl, d);
    printNodes(iterator);
    y = SLRemove(sl, e);
    printf("Head: %d\n", *(int *)sl->head->data);        
    
    destroyList(sl->head);
    SLDestroy(sl);
    SLDestroyIterator(iterator);
    
    return 0;
}