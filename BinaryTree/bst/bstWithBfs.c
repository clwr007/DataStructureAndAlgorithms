#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct Node {

    int data;
    struct Node* lc;
    struct Node* rc;
    int height;
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
    newNode->height = 0;
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

Node* findNode2(int key, Node* node){

    Node* Node2find = NULL;

    if (node == NULL){
        return 0;
    }

    if (node->lc != NULL){

        Node2find = findNode2(key,node->lc);
        if (Node2find != NULL){
            return Node2find;
        }
    }

    // ----

    if (node->data == key){
        return node;
    }

    // ----

    if ((node->rc != NULL)){

        return findNode2(key,node->rc);
    }
}


void dfs(Node* node){

    Node* process_stack[100];
    size_t process_stack_num = 0;

    process_stack[0] = node;
    process_stack_num++;
    
    while (process_stack_num > 0){
        
        Node* cursor = process_stack[process_stack_num -1];
        process_stack_num--;

        printf(" %d , ", cursor->data);

        if (cursor->rc != NULL){
            process_stack[process_stack_num] = cursor->rc;
            process_stack_num++;

        }
        if (cursor->lc != NULL){
            process_stack[process_stack_num] = cursor->lc;
            process_stack_num++;

        }


    }




}

void bfs(Node* node){
    node->height = 0;

    printf("\nbfs: ");
    Node* process_queue[100];
    size_t process_queue_num = 0;
 
    process_queue[0] = node;
    node->height = 0;
    process_queue_num++;

    while (process_queue_num > 0){
        Node* cursor = process_queue[0];
        int i;
        for (i = 0; i< process_queue_num -1; i++){
        process_queue[i] = process_queue[i+1];
        }
        
        process_queue_num--;

        printf("%d [%d], ", cursor->data, cursor->height);

        if (cursor->lc != NULL){
            cursor->lc->height = cursor->height+1;
            process_queue[process_queue_num] = cursor->lc;
            process_queue_num++;
        }

        if (cursor->rc != NULL){
            cursor->rc->height = cursor->height+1;
            process_queue[process_queue_num] = cursor->rc;
            process_queue_num++;
        }
 
   }

}

int max(int a,int b){
    if(a>b) return a;
    if(b>a) return b;
    if(a==b) return a;
}

int findHeight(Node* node){

    if (node == NULL) return -1;

    int h1 = findHeight(node->lc);
    int h2 = findHeight(node->rc);

    int h = max(h1,h2);

    return h+1;
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

Node* rightRotate(struct Node* root){

    Node* rootlc = root->lc;
    Node* lcrc = rootlc->rc;

    rootlc->rc = root;
    root->lc = lcrc;

    root->height = max(root->rc->height,root->lc->height);
    rootlc->height = max(rootlc->rc->height,rootlc->lc->height);   
    
    return rootlc; //returning the new root node

}

Node* leftRotate(struct Node* root){

    Node* rootrc = root->rc;
    Node* rclc = rootrc->lc;

    rootrc->lc = root;
    root->rc = rclc;

    root->height = max(root->rc->height,root->lc->height);
    rootrc->height = max(rootrc->rc->height,rootrc->lc->height);   
    
    return rootrc; //returning the new root node

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

    leftRotate(root);

    bfs(root);

}