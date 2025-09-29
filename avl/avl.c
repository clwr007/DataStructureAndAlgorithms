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

int getBalfac(Node* node){
    if (node == NULL) return 0;
    return findHeight(node->lc) - findHeight(node->rc);

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

    // CASE 1 LL
    if (balfactor >1 && key < root->lc->data) rightRotate(root);

    // CASE 2 RR
    if (balfactor <-1 && key > root->rc->data) leftRotate(root);

    // CASE 3 LR
    if (balfactor >1 && key > root->lc->data){
        root->lc = leftRotate(root->lc);        // the first imbalanced node's child will be leftrotated
        rightRotate(root);                      // then the first imbalanced node itself will be rightrotated

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
    if (balfactor <-1 && key < root->rc->data){
        root->rc = leftRotate(root->lc);
        rightRotate(root);

    }


}

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
    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* node3 = NULL;

    nodeinsertion(node1, 1);
    nodeinsertion(node2, 2);
    nodeinsertion(node3, 3);

}
