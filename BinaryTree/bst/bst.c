#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct Node {

    int data;
    struct Node* lc;
    struct Node* rc;

};

typedef struct Node Node;

void traverseTreeInorder(Node* node){

    if (node == NULL) return;

    if (node->lc != NULL) traverseTreeInorder(node->lc);
    
    printf("%d , ", node->data);
    
    if (node->rc != NULL) traverseTreeInorder(node->rc);
    
    // implicit return
}

typedef struct Node Node;

void traverseTreePreorder(Node* node){

    if (node == NULL) return;

    printf("%d , ", node->data);
    
    if (node->lc != NULL) traverseTreePreorder(node->lc);
    
    if (node->rc != NULL) traverseTreePreorder(node->rc);
    
    // implicit return
}

void traverseTreePostorder(Node* node){

    if (node == NULL) return;
    
    if (node->lc != NULL) traverseTreePostorder(node->lc);
    
    if (node->rc != NULL) traverseTreePostorder(node->rc);

    printf("%d , ", node->data);
    
    // implicit return
}


Node* createNode(int data){

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->lc = NULL;
    newNode->rc = NULL;

    return newNode;
}


Node* findNode(int key, Node* node){

    Node *node2Find = NULL;
    if (node == NULL) return NULL;

    if (node->lc != NULL) {
        node2Find = findNode(key,node->lc);
        // if found the node in my left subtree we dont need to proceed any further
        if(node2Find != NULL) return node2Find;
    }

    if(key == node->data) return node;
    
    // Note: we must return the return value of findNode from right subtree
    if (node->rc != NULL) return findNode(key, node->rc);
    
    // implicit return
}



void main(){

    Node* root = NULL;

    Node* node20 = createNode(20);
    Node* node10 = createNode(10);
    Node* node25 = createNode(25);
    Node* node7 = createNode(7);
    Node* node11 = createNode(11);
    Node* node21 = createNode(21);
    Node* node27 = createNode(27);

    node20->lc = node10;
    node20->rc = node25;

    node10->lc = node7;
    node10->rc = node11;

    node25->lc = node21;
    node25->rc = node27;

    /*
    traverseTreeInorder(node20);
    printf("\n");
    traverseTreePreorder(node20);
    printf("\n");
    traverseTreePostorder(node20);
    */

    Node* node2Find = findNode(10,node20);
    if(node2Find) printf("node2Find data:%d\n", node2Find->data);
    else printf("key not found\n");
    
}