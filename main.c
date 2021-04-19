#include<stdio.h>
#include<stdlib.h>
#include "rbt.h"
#include "random.h"

int main(int argc, char* argv[])
{
    RBNode* Root = &nil_leaf;
    int list[10] = {1, 3, 2, 5, 4, 7, 6, 9, 8, 10};
    for (int i = 0; i < 10; i++)
    {
        //printf("%d ", list[i]);
        redBlackInsert(&Root, list[i]);
    }
    printTree(Root);
    printf("\n");

    printf("%d\n", generate_priority());

}