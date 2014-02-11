#include "demo_avl.h" 

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

int avl_insert(avl_node* root, int item)
{
    avl_node *parent = root, *cur;
    
    if(NULL == root)
        return ERROR;

    if(avl_search(root, item, &parent))
        return OK;

    cur = (avl_node*)malloc(sizeof(avl_node));
    cur->parent = parent;
    cur->key    = item;
    cur->lchild = NULL;
    cur->rchild = NULL;
    cur->balance= 0;

    if(item < parent->key)
        parent->lchild = cur;
    else
        parent->rchild = cur;

    return OK;

}

avl_node* avl_create(int *item, int size)
{
    int i, ret;
    avl_node *root = NULL;
    if(size < 1)
        return NULL;

    root = (avl_node *)malloc(sizeof(avl_node));
    if(root == NULL)
        return NULL;
    
    memset(root, 0x00, sizeof(root));
    root->parent = NULL;
    root->lchild = NULL;
    root->rchild = NULL;
    root->key    = item[0];
    root->balance= 0;

    for(i = 1; i < size; i++)
    {
        ret = avl_insert(root, item[i]);
        if (OK != ret)
        {
            printf("avl_insert return error(code: %d)",ret);
        }
    }
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

