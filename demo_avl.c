#include "demo_avl.h" 
#ifndef true
#define true  1
#endif

#ifndef false 
#define false 0
#endif

int avl_search(avl_node* root, int item, avl_node **node)
{
    if(NULL == root)
    {
        return ERROR;
    }

    *node = root;//注意，此处容易产生误会！

    if(root->key == item)
    {
        return OK;
    }
    else if(root->key < item)
        return  avl_search(root->rchild, item, node);
    else
        return  avl_search(root->lchild, item, node);
}

static inline int Height(avl_node *node)
{
    return (node == NULL ? 0:node->height);
}

avl_node* avl_init_node(int item)
{
    avl_node *node = NULL;
    node = (avl_node *)malloc(sizeof(avl_node));
    if(node == NULL)
        return NULL;
    
    memset(node, 0x00, sizeof(node));

    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    node->key    = item;
    node->height     = 0;

    return node;
}
avl_node* avl_right_rotate(avl_node *root)
{
    avl_node *tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;

    root->height = MAX(Height(root->lchild), Height(root->rchild)) + 1;
    tmp->height = MAX(Height(tmp->lchild), Height(tmp->rchild)) + 1;
    
    return tmp;
}

avl_node* avl_left_rotate(avl_node *root)
{
    avl_node *tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;

    root->height = MAX(Height(root->lchild), Height(root->rchild)) + 1;
    tmp->height = MAX(Height(tmp->lchild), Height(tmp->rchild)) + 1;
    
    return tmp;
}

avl_node* avl_leftright_rotate(avl_node *root)
{
    root->lchild = avl_left_rotate(root->lchild);
    return avl_left_rotate(root);
}

avl_node* avl_rightleft_rotate(avl_node *root)
{
    root->rchild = avl_right_rotate(root->rchild);
    return avl_right_rotate(root);
}

avl_node* avl_insert(avl_node* root, int item)
{
    if(NULL == root)
    {
        root = avl_init_node(item);
    }
    else if(item == root->key)
        return root;
    else if(item < root->key)
    {
        root->lchild = avl_insert(root->lchild, item);
        if(Height(root->lchild) - Height(root->rchild) == 2)
        {
            if(item < root->lchild->key)
            {
                root = avl_right_rotate(root);
                }
            else
            {
                root = avl_leftright_rotate(root);
                }
        }
    }
    else if(item > root->key)
    {
        root->rchild = avl_insert(root->rchild, item);
        if(Height(root->rchild) - Height(root->lchild) == 2)
        {
            if(item > root->rchild->key)
            {
                root = avl_left_rotate(root);
                }
            else
            {
                root = avl_rightleft_rotate(root);
                }
        }
    }

    root->height = MAX(Height(root->lchild), Height(root->rchild)) + 1;
    
    return root;
}

void avl_middle_order(avl_node *root)
{
    if(NULL == root)
        return ;

    if(NULL != root->lchild)
        avl_middle_order(root->lchild);

    printf(" %d ",root->key);
    
    if(NULL != root->rchild)
        avl_middle_order(root->rchild);

    return ;
}

