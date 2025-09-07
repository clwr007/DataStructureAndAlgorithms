#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};


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

// deletes a node
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

// adds a new node
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

// reverses a linked list
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
