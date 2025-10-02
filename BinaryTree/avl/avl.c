#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Node {

    int data;
    struct Node* lc;
    struct Node* rc;
    int height;
    int level;

};

int max(int a, int b){
    if (a>b) return a;
    else return b;
}

typedef struct Node Node;

int findHeight(Node* node){

    if (node == NULL) return -1;

    int h1 = findHeight(node->lc);
    int h2 = findHeight(node->rc);

    int h = max(h1,h2);

    return h+1;
}

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = key;
    node->lc= NULL;
    node->rc= NULL;
    node->height;
    return node;
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



int getBalfac(Node* node){
    if (node == NULL) return 0;
    return findHeight(node->lc) - findHeight(node->rc);

}


Node* rightRotate(struct Node* root){

    Node* rootlc = root->lc;
    Node* lcrc = rootlc->rc;

    rootlc->rc = root;
    root->lc = lcrc;

    root->height =1+ max(
        ((root->rc!= NULL)? root->rc->height:-1),
        ((root->lc!= NULL)? root->lc->height:-1)
        );
    rootlc->height =1+ max(
        ((rootlc->rc != NULL)?rootlc->rc->height:-1),
        ((rootlc->lc != NULL)?rootlc->lc->height:-1)
        );   

    
    return rootlc; //returning the new root node

}

Node* leftRotate(struct Node* root){

    Node* rootrc = root->rc;
    Node* rclc = rootrc->lc;

    rootrc->lc = root;
    root->rc = rclc;

    root->height = 1+ max(
          ((root->rc != NULL)? root->rc->height: -1),
          ((root->lc != NULL)? root->lc->height: -1)
          );

    rootrc->height = 1 + max(
          ((rootrc->rc != NULL)? rootrc->rc->height: -1),
          ((rootrc->lc != NULL)? rootrc->lc->height: -1)
          );   
    
return rootrc; //returning the new root node

}


struct Node* nodeinsertion(struct Node* root, int key ){

    if (root == NULL) return createNode(key);

    if (key < root->data){
        root->lc = nodeinsertion(root->lc,key);
    }
    else if (key > root->data){
        root->rc = nodeinsertion(root->rc,key);
    }
    else printf("number is duplicate");

    int balfactor = getBalfac(root);

    // when balfactor > 1 tree is heavier on the left side (so right rotation)
    // when balfactor < 1 tree is heavier on the right side (so left rotation)

    // when we get the balance factor there are now 4 cases to consider
    // LL RR LR RL      (left left, right right, left right, right left)

    Node* newRoot = root;
    // CASE 1 LL
    if (balfactor >1 && key < root->lc->data) {
      newRoot = rightRotate(root);
    }
    // CASE 2 RR
    else if (balfactor <-1 && key > root->rc->data) {
      newRoot = leftRotate(root);
    }
    // CASE 3 LR
    else if (balfactor >1 && key > root->lc->data){
        root->lc = leftRotate(root->lc);        // the first imbalanced node's child will be leftrotated
        newRoot = rightRotate(root);                      // then the first imbalanced node itself will be rightrotated

        /*  
            i will use * to denote about what node the rotations are happnening
    
               16             16           16
              / \            /  \         /  \
            10   17        10*   17      8    17
           /               /            / \      
          7*              8            7   10      
           \             /                  (balanced)
            8           7  


        */
    }
    // CASE 4 RL
    else if (balfactor <-1 && key < root->rc->data){
        root->rc = leftRotate(root->lc);
        newRoot = rightRotate(root);
    }

    return newRoot;

}

// yy - yank/copy
// dd - delete line
// n-yy: nopy n lines, likewise for n-dd
// ESC - escape mode
// i - edit
// ESC -> :w


int main()
{

    /*

        (this is what we have)

        1               //level (3)
         \              -----------
          2             //level (2)
           \            -----------
            3           //level (1)
    
        (this is what we want)

            2           //level (2)
           / \          ------------   
          1   3         //level (1)
    
    */
    Node* root = NULL;

    root = nodeinsertion(root, 1);
    root = nodeinsertion(root, 2);
    root = nodeinsertion(root, 3);


    bfs(root);
}

