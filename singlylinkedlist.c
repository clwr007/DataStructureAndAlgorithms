#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//to do:
//createNode
//traverse

//first we create the struct Node
//then typedef the struct Node to just Node

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

//then we can start with the createNode function
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;

}

// then we do the traverselinkedlist function
// when creating this function we need to create two objects:
// the head and a temporary obj that acts like the cursor
// the cursor starts at the head so we equate it to head and then create a while loop that allows it to traverse 

Node* head = NULL;      //initially we set head to NULL

void traverseLL(){
    printf("[ ");
    Node* cursor = head;
    while (cursor != NULL){
        printf("%d , ",cursor->data);
        cursor= cursor->next;
    }
    printf("NULL ] \n");
}



//to do:
//deleteNode
//updateNode



void deleteNode(int key){
    Node* cursor = head;
    Node* prev = NULL;

    while(cursor->data == key && cursor != NULL){
        head == cursor->next;
        free(cursor);
        return;
    }

    while  (cursor->data != key && cursor != NULL){
        prev = cursor;
        cursor = cursor->next;
    }

    if (cursor == NULL){
        printf("element to be deleted not found");
        return;
    }

    prev->next = cursor->next;

    free(cursor);



}


void addNode(int key){
    Node* prev = NULL;
    Node* cursor = head;

    while (cursor != NULL && cursor->next != NULL && key > cursor->next->data ){
        prev = cursor;
        cursor = cursor->next;
    }

    Node* newNode = createNode(key);
    newNode->next = cursor->next;
    cursor->next = newNode;

}

Node* revLL(Node* cursor){

    if (cursor->next != NULL){
        Node* lastReadNode = revLL(cursor->next);
        lastReadNode->next = cursor;
        cursor->next = NULL;
        return cursor;

    }
    else{
        head = cursor;
        return cursor;
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

        }
    }

    
    printf("original linked list: \n");
    traverseLL();

    printf("16 got deleted: \n");
    deleteNode(16);

    traverseLL();

    printf("9 got added \n");
    addNode(9);

    traverseLL();
    printf("reversing the list: \n ");
    revLL(head);
    traverseLL();





}
