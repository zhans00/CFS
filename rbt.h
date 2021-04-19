#include <stdio.h>
#include "process.h"

#define RED 'R'
#define BLACK 'B'

typedef struct RBNode
{
  unsigned int vruntime;
  char color;
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right;
  process *process;

} RBNode;   

RBNode *root = NULL;
RBNode nil_leaf;

// A utility function to create a new BST RBNode
RBNode* newRBNode(int vruntime)
{
    RBNode *temp   = (RBNode*) malloc(sizeof(RBNode));
    temp->vruntime    = vruntime;
    temp->color  = RED;
    temp->left   = NULL;
    temp->right  = NULL;
    temp->parent = NULL;

    return temp;
}

void rotateLeft( RBNode** T, RBNode* x)
{
    RBNode *y  = x->right;    // set y
    x->right = y->left;     // turn y's left subtree into x's right subtree{
    if (y->left != &nil_leaf)
        y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == &nil_leaf)
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;            // put x on y's left
    x->parent = y;
}

void rotateRight(RBNode** T, RBNode* y)
{
    RBNode *x  = y->left;     // set x
    y->left  = x->right;    // turn x's right subtree into y's left subtree{
    if (x->right != &nil_leaf)
        x->right->parent = y;
    x->parent = y->parent;  // link y's parent to x
    if (y->parent == &nil_leaf)
        *T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;         // put y on x's right
    y->parent = x;
}

void redBlackInsertFixup(RBNode** root, RBNode* New)
{
    RBNode* temp;
    while (New->parent->color == RED)
    {
        if (New->parent == New->parent->parent->left)
        {
            temp = New->parent->parent->right;
            if (temp->color == RED)
            {
                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else {
                if (New == New->parent->right)
                {
                    New = New->parent;
                    rotateLeft(root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                rotateRight(root, New->parent->parent);
            }
        }
        else
        {
            temp = New->parent->parent->left;
    if (temp->color == RED)
    {
        New->parent->color = BLACK;
        temp->color = BLACK;
        New->parent->parent->color = RED;
        New = New->parent->parent;
    }
            else {
                if (New == New->parent->left)
                {
                    New = New->parent;
                    rotateRight(root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                rotateLeft(root, New->parent->parent);
            }
        }
    }
    root[0]->color = BLACK;
}
void redBlackInsert(RBNode** T, int vruntime)
{
    RBNode* z =  newRBNode(vruntime);
    RBNode* y =  &nil_leaf;
    RBNode* x = *T;

    // Find where to Insert new RBNode Z into the binary search tree
    while (x != &nil_leaf) {
        y = x;
        if (z->vruntime < x->vruntime)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == &nil_leaf)
        *T = z;
    else if (z->vruntime < y->vruntime)
        y->left  = z;
    else
        y->right = z;

    // Init z as a red leaf
    z->left  = &nil_leaf;
    z->right = &nil_leaf;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    redBlackInsertFixup(T, z);
}

#define MAX(a,b) (((a)>(b))?(a):(b))

int height(RBNode* root)
{
    int h = 0;

    if (root != NULL) {
        if (root == &nil_leaf)
            h = 1;
        else
        {
            int leftHeight  = height(root->left);
            int rightHeight = height(root->right);
            h = MAX(leftHeight, rightHeight) + 1;
        }
    }

    return h;
}

//中序遍历
void printTree(RBNode* root)
{
    if (root->left != &nil_leaf)
        printTree(root->left);
    printf("%d%c ", root->vruntime, root->color);
    if (root->right != &nil_leaf)
        printTree(root->right);
}