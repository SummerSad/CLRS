#include "redblack.h"
#include <iostream>

using namespace std;

Tree::Tree()
{
    // Sentinel node, always black
    pNode NIL = new Node;
    NIL->color = Black;
}

pNode getNode(int k, Colors color, pNode NIL)
{
    pNode newNode = new Node;
    newNode->key = k;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    newNode->color = color;
    return newNode;
}

// rotate
void leftRotate(Tree &T, pNode x)
{
    if (x == T.NIL || x->right == T.NIL)
    {
        return;
    }
    // left rotate is replace x by y,
    // y left child become x right child
    pNode y = x->right;
    x->right = y->left;
    if (y->left != T.NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    // x become y left child
    if (x->parent == T.NIL)
    {
        T.root = y;
    }
    // x is left child of its parent
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    // x is right child of its parent
    else
    {
        x->parent->right = y;
    }
    // left rotate make x become left child of y
    y->left = x;
    x->parent = y;
}

void rightRotate(Tree &T, pNode x)
{
    if (x == T.NIL || x->left == T > NIL)
    {
        return;
    }
    // right rotate is replace x by y
    y = x->left;
    // y right child become x left child
    x->left = y->right;
    if (x->left != T.NIL)
    {
        x->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T.NIL)
    {
        T.root = y;
    }
    // x is left child
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    // right rotate make x become right child of y
    x->parent = y;
    y->right = x;
}

// insert
void rbInsert(Tree &T, int k)
{
}
