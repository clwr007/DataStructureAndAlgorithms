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
   Node* process_queue[100];
   size_t process_queue_num = 0;

   process_queue[0] = node;
   process_queue_num++;

   while (process_queue_num > 0){
    Node* cursor = process_queue[0];
    int i;
    for (i = 0; i< process_queue_num -1; i++){
        process_queue[i] = process_queue[i+1];
    }
    process_queue_num--;

    printf("%d , ", cursor->data);

    if (cursor->lc != NULL){
        process_queue[process_queue_num] = cursor->lc;
        process_queue_num++;
    }

    if (cursor->rc != NULL){
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

int findlvl(Node* node){

    if (node == NULL) return 0;

    int h1 = findlvl(node->lc);
    int h2 = findlvl(node->rc);

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

    node7->lc = NULL;
    node7->rc = NULL;

    node11->lc = NULL;
    node11->rc = NULL;

    node21->lc = NULL;
    node21->rc = NULL;

    node27->lc = NULL;
    node27->rc = NULL;
    
    /*
    traverseTreeInorder2(node20);
    printf("\n");
    
    traverseTreeInorder(node20);
    printf("\n");
    traverseTreePreorder(node20);
    printf("\n");
    traverseTreePostorder(node20);
    

    Node* node2Find = findNode(10, node20);
    if (node2Find != NULL){
        printf("Node found, data stored in that node is: %d", node2Find->data);
    }else{
        printf("Node not found");
    }

    */



    //-------------------------------------------------



    /*
            20
           /   \ 
          10    25
         / \    / \
        7  11  21  27
    
    */


    int h = findlvl(node20);
    printf("h=%d", h);

    /*
    printf("this is bfs: \n");
    bfs(node20);

    printf("\n");
    printf("this is dfs: \n");
    dfs(node20);
   
    */
}