#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

//Compares int data types
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

//Compares char data types
int compareChars(void * val1, void * val2) {
    
    char * x = (char *)val1;
    char * y = (char *)val2;
    
    if (*x < *y) {
        return -1;
    } else if (*x == *y) {
        return 0;
    }
    
    return 1;
}

//Compare float data types
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

//Compares double data types
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


//frees up the memory allocated for the node being passed
void destroyNode(void *n) {
     
    Node * no = (Node*)n;                           //create a temporary local node
    free(no);                                       //free the memory allocated for that node
     
    return;
}
 
 
//iterates through the sorted list destroying each node along the way
void destroyList(void *n) {
     
    Node *node = (Node*)n;
    if (node->next == NULL) {
        destroyNode(n);
        return;
    }
 
    destroyList(node->next);
    destroyNode(n);
    return;
     
}


//uses the iterator to move through a list and print out the contents
void printNodes(SortedListIteratorPtr iter, int indicator) {
    
    void * item = NULL;
    
    if (indicator == 0) {
        while (iter->node != NULL) {
            
            item = SLGetItem(iter);
            printf("%d\n", *(int*)item);
            
        }
    } else if (indicator == 1) {
        while (iter->node != NULL) {
            
            item = SLGetItem(iter);
            printf("%.2f\n", *(float*)item);
            
        }
    } else if (indicator == 2) {
        while (iter->node != NULL) {
            
            item = SLGetItem(iter);
            printf("%c\n", *(char*)item);
        }
    } else if (indicator == 3) {
        while (iter->node != NULL) {
            item = SLGetItem(iter);
            printf("%.2f\n", *(double*)item);
        }
    }
    
}

int main(int argc, char **argv) {
    
    //arrays of random values for testing integers, floats
    int array[] = {5, 3, 7, 2, 1, 0, 9, 8, 10, 11, 6, 4, 2, 9};
    float arr[] = {3.14, 2.76, 3.11, 4.20, 12.22, 8.30, 3.04, 3.05, 10.30, 0};
    char charr[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    double darr[] = {45.7, 63.8, 99.9, 17.83, 31.32, 100.3, 3245.6};
        
    //Create the function pointers for comparison and destruction
    int (*integer)(void *, void*) = compareInteger;
    void (*destroy)(void *) = destroyNode;

    //Create a sortedlist pointer
    SortedListPtr sl = SLCreate(integer, destroy);
    
    //Insert all of the values from the array into the sorted list 
    int x = 0;
    void * v = NULL;
    int i = 0;
    for (i = 0; i < 14; i++) {
        v = &array[i];
        x = SLInsert(sl, v);
    }
    
    //Create a list iterator to move through the list and print out the values
    SortedListIteratorPtr iterator = SLCreateIterator(sl);
    printNodes(iterator, 0);                                    //print content of the sorted list, the second variable is an indicator to indicate which data type is in the list
    printf("\n");
           
    //Remove a couple of values from the sorted list to make sure it works properly
    v = &array[7];                                              //8
    int y = SLRemove(sl, v);
    v = &array[5];                                              //0
    y = SLRemove(sl, v);
    v = &array[13];                                             //9
    y = SLRemove(sl, v);  
    iterator->node = sl->head;                                  //set the iterator's node pointing to the head of the list since changes were made
    printNodes(iterator, 0);
    printf("\n");
    
    //Destroy the list and set list->head to NULL afterwards 
    destroyList(sl->head);
    sl->head = NULL;
    
    //Check to see if the list is empty  
    iterator->node = sl->head;                 
    printNodes(iterator, 0);   
    printf("\n");
    
    //Destroy the list and iterator 
    SLDestroy(sl);
    SLDestroyIterator(iterator);
    
    
    //The following is a float test
    int (*floater)(void *, void*) = compareFloats;
    SortedListPtr list = SLCreate(floater, destroy);

    //Insert the values of arr into the new sorted list
    v = NULL;
    x = 0;
    for (i = 0; i < 10; i++) {
        v = &arr[i];
        x = SLInsert(list, v);
    }
    
    //Make sure the list is sorted and the values were copied correctly
    SortedListIteratorPtr ptr = SLCreateIterator(list);
    printNodes(ptr, 1);
    printf("\n");
    
    v = &arr[5];            //8.30
    y = SLRemove(list, v);
    v = &arr[4];            //12.22
    y = SLRemove(list, v);    
    v = &arr[9];            //0
    y = SLRemove(list, v);
    
    //Check to see if our values were removed properly    
    ptr->node = list->head;
    printNodes(ptr, 1);
    printf("\n");
    
    //Destroy the sorted list, the contents of the list, and the iterator
    destroyList(list->head);
    SLDestroy(list); 
    SLDestroyIterator(ptr);
    
    
    //The following is a char test
    int (*character)(void*, void*) = compareChars;
    SortedListPtr lst = SLCreate(character, destroy);
    
    //Insert the values of charr into the new sorted list
    v = NULL;
    x = 0;
    for (i = 0; i < 11; i++) {
        v = &charr[i];
        x = SLInsert(lst, v);
    }
    
    SortedListIteratorPtr itr = SLCreateIterator(lst);
    printNodes(itr, 2);
    printf("\n");
    
    //Remove some random values
    v = &charr[2];
    y = SLRemove(lst, v);               //l
    v = &charr[4];
    y = SLRemove(lst, v);               //o
    v = &charr[6];
    y = SLRemove(lst, v);               //w  
    
    //Check to see if the values were properly removed
    itr->node = lst->head;
    printNodes(itr, 2);    
    
    //Destroy the sorted list, the contents of the list, and the iterator
    destroyList(lst->head);
    SLDestroy(lst);
    SLDestroyIterator(itr);
    
    
    //The following is a double test
    int (*doubles)(void *, void *) = compareDoubles;
    SortedListPtr slp = SLCreate(doubles, destroy);
    
    //Insert the values of darr into the sorted list slp
    v = NULL;
    x = 0;
    for (i = 0; i < 7; i++) {
        v = &darr[i];
        x = SLInsert(slp, v);        
    }
    
    //Print the list to make sure everything was added properly
    SortedListIteratorPtr slip = SLCreateIterator(slp);
    printNodes(slip, 3);
    printf("\n");
    
    //Remove some values
    v = &darr[3];
    y = SLRemove(slp, v);                   //17.83
    v = &darr[0];
    y = SLRemove(slp, v);                   //45.7
    v = &darr[6];
    y = SLRemove(slp, v);                   //3245.6
    
    //Check list to see if the changes were properly made
    slip->node = slp->head;
    printNodes(slip, 3);
    printf("\n");        
    
    //Destroy the sorted list, the contents of the list, and the iterator
    destroyList(slp->head);
    SLDestroy(slp);
    SLDestroyIterator(slip);
    
    
    return 0;
}