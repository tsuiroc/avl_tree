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
    if(tmp->rchild)
        tmp->rchild->parent= root;
    tmp->rchild = root;
    tmp->parent = root->parent;
    root->parent = tmp;

    root->height = MAX(Height(root->lchild), Height(root->rchild)) + 1;
    tmp->height = MAX(Height(tmp->lchild), Height(tmp->rchild)) + 1;
    
    return tmp;
}

avl_node* avl_left_rotate(avl_node *root)
{
    avl_node *tmp = root->rchild;
    root->rchild = tmp->lchild;
    if(tmp->lchild)
        tmp->lchild->parent= root;
    tmp->lchild = root;
    tmp->parent = root->parent;
    root->parent = tmp;

    root->height = MAX(Height(root->lchild), Height(root->rchild)) + 1;
    tmp->height = MAX(Height(tmp->lchild), Height(tmp->rchild)) + 1;
    
    return tmp;
}

avl_node* avl_leftright_rotate(avl_node *root)
{
    root->lchild = avl_left_rotate(root->lchild);
    return avl_right_rotate(root);
}

avl_node* avl_rightleft_rotate(avl_node *root)
{
    root->rchild = avl_right_rotate(root->rchild);
    return avl_left_rotate(root);
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
        root->lchild->parent = root;
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
        root->rchild->parent = root;
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

void avl_delete(avl_node *root, int item)
{
    if(NULL == root)
        return ;

    if(item < root->key)
    {
        avl_delete(root->lchild, item);
        if(Height(root->rchild) - Height(root->lchild) == 2)
        {
            avl_left_rotate(root);
        }
    }
    else if(item > root->key)
    {
        avl_delete(root->rchild, item);
        if(Height(root->lchild) - Height(root->rchild) == 2)
        {
            avl_right_rotate(root);
        }
    }
    else
    {
        avl_node *tmp = NULL;
        if(root->lchild != NULL && root->rchild != NULL)
        {
            if(Height(root->lchild) > Height(root->rchild))
            {
                tmp = root->lchild;
                while(tmp->rchild != NULL) tmp = tmp->rchild;
                
                root->key = tmp->key;
                avl_delete(root->lchild, tmp->key);
            }
            else
            {
                tmp = root->rchild;
                while(tmp->lchild != NULL) tmp = tmp->lchild;
                
                root->key = tmp->key;
                avl_delete(root->rchild, tmp->key);
            }
        
        }
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            root->parent->rchild = root->rchild;
            root->rchild->parent = root->parent;
            if(root->parent)
                root->parent->height -= 1;
            free(root); root = NULL;
            return;
        }
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            root->parent->lchild = root->lchild;
            root->lchild->parent = root->parent;
            if(root->parent)
                root->parent->height -= 1;
            free(root); root = NULL;
            return;
        }
        else if(root->lchild == NULL && root->rchild == NULL)
        {
            if(root->parent != NULL && root->parent->lchild != NULL && root->parent->lchild->key == item)
            {
                if(!root->parent->rchild)
                    root->parent->height -= 1;
                root->parent->lchild = NULL;
            }
            else
            {
                if(!root->parent->lchild)
                    root->parent->height -= 1;
                root->parent->rchild = NULL;
            }

            free(root); root = NULL;
        }
    }

    return ;
}

void avl_distory(avl_node *root)
{
    if(NULL == root)
        return ;

    if(NULL != root->lchild)
        avl_distory(root->lchild);

    if(NULL != root->rchild)
        avl_distory(root->rchild);

    free(root);

    return ;
}

void avl_middle_order(avl_node *root)
{
    if(NULL == root)
        return ;

    avl_middle_order(root->lchild);

    printf("\n%d ",root->key);
    printf("(l:%d ", root->lchild ? root->lchild->key : -1);
    printf("parent:%d ", root->parent? root->parent->key : -1);
    printf("height:%d ", root->height);
    printf("r:%d)", root->rchild ? root->rchild->key : -1);
    
    avl_middle_order(root->rchild);

    return ;
}

