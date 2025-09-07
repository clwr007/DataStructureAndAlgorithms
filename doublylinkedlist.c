#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};

//createNode
//insertAtHead
//traverseLL
//deleteNode
//addNdde
//reverseLL

typedef struct Node Node;

Node* head = NULL;

Node* createNode(int data){

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertAtHead(int key){

    Node* newNode = createNode(key);
    if (head == NULL){
        head = newNode;
        return;
    }

    head->prev = newNode;
    newNode->next = head;
    head = newNode;

}

void traverseLL(){

    printf("[");
    printf("NULL\n");
    Node* cursor= head;
    while (cursor != NULL){
        printf("Node: %d",cursor->data);
        if(cursor->prev != NULL) {
            printf("     Node prev: %d",cursor->prev->data);
        }
        printf("\n");
        cursor = cursor->next;
    }
   
    printf(" NULL ");
    printf("] \n");
}

void delNode(int key){
    Node* cursor = head;
    Node* prev = cursor->prev;
    Node* next = cursor->next;
    while(cursor != NULL && key != cursor->data){
        cursor = cursor->next;
    }

    if(cursor == NULL){
        printf("element to be deleted not found");
    }

    prev->next = cursor->next;
    next->prev = cursor->prev;
    free(cursor);
    
}

void addNode(int key){
    Node* cursor = head;

    while ( cursor != NULL && cursor->next != NULL && key > cursor->next->data){
        cursor = cursor->next;
    }
    Node* newNode = createNode(key);
    
    newNode->next = cursor->next;
    cursor->next->prev = newNode;

    cursor->next = newNode;
    newNode->prev = cursor;

}


/*
[NULL
Node: 0
Node: 2     Node prev: 0
Node: 4     Node prev: 2
Node: 6     Node prev: 4
Node: 8     Node prev: 6
Node: 10     Node prev: 8
Node: 12     Node prev: 10
Node: 14     Node prev: 12
Node: 16     Node prev: 14
Node: 18     Node prev: 16
 NULL ]
*/
void revLL(){
    Node* cursor = head;
    while (cursor != NULL){
        head = cursor;

        //printf("cursor %d\n", cursor->data);

        Node* cursorprev = cursor->prev;
        Node* cursornxt = cursor ->next;

        cursor->next = cursorprev;
        cursor->prev = cursornxt;

        cursor = cursornxt;

    }

}


int main(){

    int i=0;
    for(i=0;i<10;i++){
        Node* newNode = createNode(i*2);
        if (head == NULL){
            head = newNode;
        }
        else{
            Node* cursor = head;
            while(cursor!= NULL && cursor->next != NULL){
                cursor = cursor->next;
            }
            cursor->next = newNode;
            newNode->prev = cursor;
        }
    }


    traverseLL();

    /*
    insertAtHead(15);
    traverseLL();
    */

    revLL();
    traverseLL();

}
