#include <stdio.h>
#include <stdlib.h>

#define RED 'R'
#define BLACK 'B'

typedef struct process
{
    unsigned int left_time;
    unsigned int start_time;
    unsigned int waiting_time;
    unsigned int response_time;
    int preempted;
    int priority;

} process;

typedef struct gclock
{
    unsigned int ticks;
} gclock;

typedef struct RBNode
{
  unsigned int vruntime;
  char color;
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right;
  process *process;

} RBNode;   

// RBNode *root = NULL;
RBNode nil_leaf;

// A utility function to create a new BST RBNode
RBNode* newRBNode(process* p, unsigned int vruntime)
{
    RBNode *temp   = (RBNode*) malloc(sizeof(RBNode));
    temp->vruntime = vruntime;
    temp->process = p;
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

RBNode* left(RBNode* T) {
    RBNode* temp = T;

    while(temp->left != &nil_leaf){
        temp = temp->left;
    } 

    return temp;
} 

    void rbTransplant(RBNode **root, RBNode* u, RBNode* v){
        if (u->parent == &nil_leaf  ) {
            *root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
RBNode* redBlackInsert(RBNode** T, process* p, unsigned int vruntime)
{
    RBNode* z =  newRBNode(p, vruntime);
    RBNode* y =  &nil_leaf;
    RBNode* x = *T;
    // printf("%d\n", p->start_time );
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

    if(z->vruntime == 0 && z->parent != &nil_leaf && z->parent != NULL) {
        z->vruntime = (z->parent->vruntime)/2;
    }

    // Ensure the Red-Black property is maintained
    redBlackInsertFixup(T, z);

    return z;
}



void fixDelete(RBNode* x, RBNode** root) {
        RBNode* s;
        while (x != *root && x->color == 'B') {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 'R') {
                    // case 3.1
                    s->color = 'B';
                    x->parent->color = 'R';
                    rotateLeft(root, x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 'B' && s->right->color == 'B') {
                    // case 3.2
                    s->color = 'R';
                    x = x->parent;
                } else {
                    if (s->right->color == 'B') {
                        // case 3.3
                        s->left->color = 'B';
                        s->color = 'R';
                        rotateRight(root, s);
                        s = x->parent->right;
                    } 

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 'B';
                    s->right->color = 'B';
                    rotateLeft(root, x->parent);
                    x = *root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 'R') {
                    // case 3.1
                    s->color = 'B';
                    x->parent->color = 'R';
                    rotateRight(root, x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 'B' && s->right->color == 'B') {
                    // case 3.2
                    s->color = 'R';
                    x = x->parent;
                } else {
                    if (s->left->color == 'B') {
                        // case 3.3
                        s->right->color = 'B';
                        s->color = 'R';
                        rotateLeft(root, s);
                        s = x->parent->left;
                    } 

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 'B';
                    s->left->color = 'B';
                    rotateRight(root, x->parent);
                    x = *root;
                }
            } 
        }
        x->color = 'B';
    }


RBNode* delete(RBNode** node) {
        // find the node containing key
        RBNode* z = left(*node);
        RBNode* x, *y;
        RBNode* ans = z;
        y = z;
        char y_original_color = y->color;
        if (z->left == &nil_leaf) {
            // if(z->right == &nil_leaf || z->right == NULL){
            //     z = &nil_leaf;
            //     return ans;
            // }
            x = z->right;
            rbTransplant(node, z, z->right);
        }  
        // free(z);
        if (y_original_color == 'B'){
            fixDelete(x, node);
        }
        return ans;
    }

int compare(const void *s1, const void *s2)
{
    process *p1 = (process *)s1;
    process *p2 = (process *)s2;
    if (p1->start_time == p2->start_time)
        return p1->priority < p2->priority;
    return p1->start_time > p2->start_time;
}



// #define MAX(a,b) (((a)>(b))?(a):(b))

// int height(RBNode* root)
// {
//     int h = 0;

//     if (root != NULL) {
//         if (root == &nil_leaf)
//             h = 1;
//         else
//         {
//             int leftHeight  = height(root->left);
//             int rightHeight = height(root->right);
//             h = MAX(leftHeight, rightHeight) + 1;
//         }
//     }

//     return h;
// }

// //中序遍历
void printTree(RBNode* root)
{
    if(root == &nil_leaf){
        printf("empty\n");
        return;
    }

    if (root->left != &nil_leaf)
        printTree(root->left);
    fprintf(stdout, "%d %d\n", root->process->left_time, root->process->start_time);
    fflush(stdout);
    // printf("%d%c ", root->vruntime, root->color);
    if (root->right != &nil_leaf)
        printTree(root->right);
}

