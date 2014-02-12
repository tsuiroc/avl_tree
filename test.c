#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo_avl.h"

int main(int argc, char *argv[])
{

    int       data[] = {1, 7, 2, 4, 9, 3, 10, 18, 12};
    int i;
    avl_node *root = NULL;

    for(i = 0; i < sizeof(data)/sizeof(data[0]); i++)
    {
        root = avl_insert(root, data[i]);
    }

    avl_middle_order(root);
        avl_delete(root, 10);
    avl_middle_order(root);
    return 0;
}
