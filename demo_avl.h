#ifndef _AVL_TREE
#define _AVL_TREE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK    1
#define ERROR 0

#define LH    1  
#define EH    0
#define RH   -1
#define MAX(a,b) ((a)>(b) ? (a):(b))

typedef struct AVL_NODE avl_node;
struct AVL_NODE 
{
    int key;
    int height;         
    avl_node *lchild;
    avl_node *rchild;
    avl_node *parent;
};

int avl_search(avl_node* root, int item, avl_node **node);

avl_node* avl_insert(avl_node* root, int item);

avl_node* avl_create(int *item, int size);

void avl_middle_order(avl_node *root);

#endif

