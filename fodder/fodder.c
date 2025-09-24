#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Node {

    int data;
    struct Node* lc;
    struct Node* rc;
    int level;
};

typedef struct Node Node;

Node* createNode(int data){

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->level = 0;
    newNode->lc = NULL;
    newNode->rc = NULL;

    return newNode;
}

void traverseTreeInorder(Node* node){

    if (node == NULL) return;

    if (node->lc != NULL) traverseTreeInorder(node->lc);
    
    printf("%d , ", node->data);
    
    if (node->rc != NULL) traverseTreeInorder(node->rc);
    
    // implicit return
}

void buildtree(Node* node , int number){

    if (number > node->data){
        if (node->rc == NULL){
            
            Node* NewNode = createNode(number);
            node->rc = NewNode;
        }
        else buildtree(node->rc, number);

    }else if (number < node->data){
        if(node->lc == NULL){
            Node* NewNode = createNode(number);
            node->lc = NewNode;
            
        }
        else buildtree(node->lc, number);

    }else printf("number is duplicate ");
}


void main(){

    Node* root = NULL;
    int key = -1;

    while(1)
    {
        printf("\nEnter key to add to tree (or -1 to stop):");
        scanf("%d", &key);
        if(key == -1) break;
        if(root == NULL) {
            root = createNode(key);
        }
        else {
            buildtree(root, key);
        }

    }
    
    printf("\nTree: %n");
    traverseTreeInorder(root);
    
    bfs(root);
}