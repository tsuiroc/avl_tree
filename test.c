#include <stdio.h>
#include <stdlib.h>
#include "demo_avl.h"

int main(int argc, char *argv[])
{

    int       data[] = {1, 3, 5, 6, 2, 3333};
    avl_node *root;

    root = avl_create(data, sizeof(data)/sizeof(data[0]));

    avl_middle_order(root);
    return 0;
}
