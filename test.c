#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo_avl.h"

int main(int argc, char *argv[])
{

    int       data[] = {1, 3, 5, 6, 2, 3333};
    int i;
    avl_node *root = NULL;

    for(i = 0; i < sizeof(data)/sizeof(data[0]); i++)
    {
        root = avl_insert(root, data[i]);
        }

        printf("root %d\n",root->key);
    avl_middle_order(root);
    return 0;
}
