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
    newNode->level = 0;
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
    node->level = 0;

    printf("\nbfs: ");
    Node* process_queue[100];
    size_t process_queue_num = 0;
 
    process_queue[0] = node;
    node->level = 0;
    process_queue_num++;

    while (process_queue_num > 0){
        Node* cursor = process_queue[0];
        int i;
        for (i = 0; i< process_queue_num -1; i++){
        process_queue[i] = process_queue[i+1];
        }
        
        process_queue_num--;

        printf("%d [%d], ", cursor->data, cursor->level);

        if (cursor->lc != NULL){
            cursor->lc->level = cursor->level+1;
            process_queue[process_queue_num] = cursor->lc;
            process_queue_num++;
        }

        if (cursor->rc != NULL){
            cursor->rc->level = cursor->level+1;
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
    
    printf("\nTree: \n");
    traverseTreeInorder(root);
    
    bfs(root);
}
