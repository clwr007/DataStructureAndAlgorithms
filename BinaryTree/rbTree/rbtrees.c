// Red Black Trees

/*
To Do:

- create node
- initialise tree
- traverse and print color 
- findmin and findmax (return key)
- insert , fix insert
- left rotate and right rotate (color correction after rotations)
- print tree (with visual indentation)
- isRedBlack tree (return true or false)

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum {RED,BLACK,NONE} Color;

struct Node {
    int data;
    struct Node* rc;
    struct Node* lc;
    Color color;
    int level;
};
typedef struct Node Node;

Color retcomplColor(Color color){
    if (color == RED) return BLACK;
    if (color == BLACK) return RED;
    return BLACK;
}

Node* createNode(int key, Color parentColor,int level){

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->color = retcomplColor(parentColor);
    newNode->level = level;

    if (parentColor == NONE ) newNode->color = BLACK;

    newNode->rc = NULL;
    newNode->lc = NULL;
    
    return newNode;

}
// when doing a bfs we keep track of queue and size of queue
// so as the size of the queue increases we increment our sizeofqueue variable 
// our queue is of type Node , we create a cursor after entering a while loop (this while loop will go on until queue num is zero)
// we create a for loop that works on first in first out basis
// which means queue[i] = queue[i+1] effectively removing our first item in queue but also making sure it was stored in cursor
// 
void printTree(Node* root){

    root->level = 0;
    Node* queue[100];
    size_t queuenum = 0;
    
    queue[0] = root;
    queuenum++;
    int currentlvl =0;
    
    while (queuenum > 0){
        if (queue[0] == NULL) {
            for (int i = 0; i < queuenum - 1; i++){
                queue[i] = queue[i + 1];
            }
            queuenum--;
            printf("nil ");
            continue;
        }
        Node* cursor = queue[0];
        for (int i = 0 ; i< queuenum-1 ; i++ ){
            queue[i]=queue[i+1];
        }
        //first element from our queue has been popped so we decrement our queuenum
        queuenum--;
        if (queuenum > 0 && cursor->level > currentlvl) {
            printf("\n");
            currentlvl = queue[0]->level;
        }
        
        printf("currentlvl = %d ", currentlvl);
        printf("queuelvl = %d ", queue[0]->level);
        
        printf(" %d",cursor->data);
        if(cursor->color == BLACK) printf("(B) ");
        else if(cursor->color == RED) printf("(R) ");
        else printf("(B) ");
        if (cursor->lc != NULL){
            cursor->lc->level = cursor->level+1;
            cursor->lc->color = retcomplColor(cursor->color);
            //adding to queue
            queue[queuenum] = cursor->lc;
            queuenum++;
        }
        else {
            queue[queuenum] = NULL;
            queuenum++;
        }
        if (cursor->rc != NULL){
            cursor->rc->level = cursor->level+1;
            cursor->rc->color = retcomplColor(cursor->color);
            //adding to queue
            queue[queuenum] = cursor->rc;
            queuenum++;
        }
        else {
            queue[queuenum] = NULL;
            queuenum++;
        }
            
    }



}
void printTree2(Node* root){

    root->level = 0;
    Node* queue[100];
    size_t queuenum = 0;
    
    queue[0] = root;
    queuenum++;
    int currentlvl =0;
    
    while (queuenum > 0){
        Node* cursor = queue[0];
        for (int i = 0 ; i< queuenum-1 ; i++ ){
            queue[i]=queue[i+1];
        }
        //first element from our queue has been popped so we decrement our queuenum
        queuenum--;
        if (queuenum > 0 && cursor->level > currentlvl) {
            printf("\n");
            currentlvl = queue[0]->level;
        }
        
        printf(" %d",cursor->data);
        if(cursor->color == BLACK) printf("(B) ");
        else if(cursor->color == RED) printf("(R) ");
        else printf("(B) ");
        if (cursor->lc != NULL){
            cursor->lc->level = cursor->level+1;
            cursor->lc->color = retcomplColor(cursor->color);
            //adding to queue
            queue[queuenum] = cursor->lc;
            queuenum++;
        }
        else {
            queue[queuenum] = NULL;
            queuenum++;
        }
        if (cursor->rc != NULL){
            cursor->rc->level = cursor->level+1;
            cursor->rc->color = retcomplColor(cursor->color);
            //adding to queue
            queue[queuenum] = cursor->rc;
            queuenum++;
        }
        else {
            queue[queuenum] = NULL;
            queuenum++;
        }
            
    }



}


int main(){
    Node* root;
    root = createNode(2,NONE,0);   //root
    root->lc = createNode(1,BLACK,1);
    root->rc = createNode(3,BLACK,1);
    root->rc->rc = createNode(5,RED,2);

    printTree2(root);

}