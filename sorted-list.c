#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

//A function that creates a node struct and returns a pointer to it
Node* createNode(void *data, Node *nxt, Node *prv) {
   
    Node * node = malloc(sizeof(Node));                                 //allocates memory for the node
    if (node == NULL) {                                                 //checks to see if malloc successfully allocated memory
        printf("Error! Failed to allocate memory for a new node.\n");
        return NULL;
    }
    
    node->data = data;                                                  //assign the data to the node
    node->next = nxt;                                                   //set the node's next node to nxt
    node->prev = prv;                                                   //set the previous node's node to prv
    
    return node;                                                        //return the node
}

//Creates a sorted list and returns a pointer to it
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
    
    SortedListPtr sl = malloc(sizeof(struct SortedList));               //allocate memory for the sorted list pointer struct
    
    //check to see if malloc was a success
    if (sl == NULL) {
        printf("Error! Failed to allocate memory for sorted list pointer.\n");
        return NULL;
    }
    
    sl->cf = cf;                                                        //assign the sorted list's compare function to the one passed
    sl->df = df;                                                        //assign the sorted list's destruct function to the one passed
    sl->head = NULL;                                                    //set the head of the list to null
    
    return sl;
}

//Destroys a sorted list pointer
void SLDestroy(SortedListPtr list) {
    
    free(list);
    
    return;
    
}

//allocates memory for a new sorted list iterator
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
    
    SortedListIteratorPtr iterator = malloc(sizeof(SortedListIteratorPtr));         //allocates memory for a sorted list iterator
    
    //check to see if the memory was allocated successfully, if not, print an error and return null
    if (iterator == NULL) {
        printf("Failed to create SortedListIteratorPtr.\n");
        return NULL;
    }
    
    iterator->node = list->head;                                                    //sets the iterator node to the head of the sorted list
    
    return iterator;
}

//frees up the memory allocated for a sorted lister iterator pointer
void SLDestroyIterator(SortedListIteratorPtr iter) {
    
    free(iter);
    
    return;
}

//inserts the new data item in sorted order
int SLInsert(SortedListPtr  list, void *newObj) {
    
    int x = 2;                                                                  //we know x will be either 0, 1, or -1 so we set it = to 2
    int left = 2;                                                               //will keep tabs on whether or not the previous node was bigger or smaller
    
    if (list->head == NULL) {                                                   //data list is empty
        list->head = createNode(newObj, NULL, NULL);                            //create new node with the data
        return 1;
    } else {
        Node *currNode = list->head;                                            //create a temporary node to traverse the list
        x = list->cf(currNode->data,newObj);                                    //compare the head node data to the new data
        if (x == -1 || x == 0) {                                                //second data value is larger
            Node *node = createNode(newObj, currNode, NULL);                    //create new node with the new data value
            currNode->prev = node;
            list->head = node;                                                  //set the head of the list to the new node
            return 1;
        }
        
        Node *temp = NULL;                                                      //a temporary node to keep track of the previous node
        while (currNode != NULL) {                                              //otherwise, traverse the list
        
            x = list->cf(currNode->data, newObj);                               //compare the current node's data with the new data
            if (x == -1 && left == 1) {                                         //second value is larger than current value, but smaller than previous value
                break;                                          
            } else if (x == 0) {                                                //value already exists
                break;
            } else if (currNode->next == NULL) {
                Node *node = createNode(newObj, NULL, currNode);               //this data value is the smallest in the list so it goes at the end
                currNode->next = node;                                         //set the current node's next value point to the new node
                return 1;
            }
            
            //otherwise, keep traversing the list
            left = x;
            temp = currNode;
            currNode = currNode->next;
        }
        
        Node *node = createNode(newObj, currNode, temp);                        //create a new node with temp being the previous node and currNode being the next node
        temp->next = node;                                                      //set the previous node's next value equal to the new node

        return 1;
    }
     
    
    return 0;
    
}

int SLRemove(SortedListPtr list, void *newObj) {
    
    Node * node = NULL;                                 //a node struct to temporarily store node values
    int comp = list->cf(list->head->data, newObj);      //store the result of the compare function
    
    //the first node in the list is our target
    if (comp == 0) {
        
        node = list->head->next;                        //get the next node in the list after the head and store it in node
        list->df(list->head);                           //destroy the current list head
        list->head = node;                              //set the new list head to node (next element in list)
        return 1;
    }
    
    node = list->head;                                  //otherwise set node equal to the head of the list
    
    Node *prv = NULL;
    
    //search the list until you reach the end or find your target value
    do {
        prv = node;
        node = node->next;
        if (node == NULL) {
            return 0;                                   //reached end of the list without finding our target
        }
        comp = list->cf(node->data, newObj);            //compare current node data with our target value

    } while (comp != 0);
    
    prv->next = node->next;                             //set the previous node's next pointer point to the current node's next node
    if (node->next != NULL) {                           //if the next node is not a null
        node->next->prev = prv;                         //set the next node's previous pointer point to our previous node prv
    }
    
    list->df(node);                                     //destroy our target node 
    return 1;
    
}

//Gets the next data item in our sorted list
void * SLNextItem(SortedListIteratorPtr iter) {
    
    void * item = NULL;                                 //create a void pointer variable to store our target data
    
    if (iter->node == NULL) {                           //if the iterator's node points to null, then we reached the end of the list
        
        return item;
        
    }
    item = iter->node->data;                            //our data item is the iterator's current node's data
    iter->node = iter->node->next;                      //have our iterator point to the next node in the list
    
    return item;
}

void * SLGetItem(SortedListIteratorPtr iter) {
    
    void * item = SLNextItem(iter);                     //call the next item in the sorted list and return that value
    
    return item;
}