#include "redblack.h"
#include <iostream>

using namespace std;

Tree::Tree()
{
    // Sentinel node, always black
    NIL = new Node;
    NIL->color = Black;
    root = NIL;
}

Tree::~Tree()
{
    delete NIL;
}

pNode getNode(int k, Colors color, pNode NIL)
{
    pNode newNode = new Node;
    if (!newNode)
    {
        cout << "Can't make node" << endl;
    }
    newNode->key = k;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    newNode->color = color;
    return newNode;
}

void printPreOrder(pNode root, pNode NIL, int indent)
{
    if (root != NIL)
    {
        // print in preorder
        for (int i = 0; i < indent; ++i)
        {
            cout << ' ';
        }
        cout << root->key << " ";
        if (root->color == Black)
        {
            cout << "B" << endl;
        }
        else
        {
            cout << "R" << endl;
        }

        printPreOrder(root->left, NIL, indent + 4);
        printPreOrder(root->right, NIL, indent + 4);
    }
    else
    {
        for (int i = 0; i < indent; ++i)
        {
            cout << ' ';
        }
        cout << "NULL" << endl;
    }
}

void delPostOrder(pNode &root, pNode NIL)
{
    if (root != NIL)
    {
        delPostOrder(root->left, NIL);
        delPostOrder(root->right, NIL);
        delete root;
    }
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
    if (x == T.NIL || x->left == T.NIL)
    {
        return;
    }
    // right rotate is replace x by y
    pNode y = x->left;
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
    pNode y = T.NIL;
    pNode x = T.root;
    pNode z = getNode(k, Red, T.NIL);
    while (x != T.NIL)
    {
        if (x->key == k)
        {
            cout << k << " already exist" << endl;
            delete z;
            return;
        }
        if (x->key < k)
        {
            y = x;
            x = x->right;
        }
        else
        {
            y = x;
            x = x->left;
        }
    }
    // Empty tree
    if (y == T.NIL)
    {
        T.root = z;
    }
    else if (y->key > k)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->parent = y;
    // Recolor and rotate when violate red black tree
    rbInsertFixUp(T, z);
}

void rbInsertFixUp(Tree &T, pNode z)
{
    // violate z and z->parent same Red
    // Terminate when z is root os parent(z) is Black
    while (z->parent->color == Red)
    {
        if (z->parent == z->parent->parent->left)
        {
            // y is right uncle(z)
            pNode y = z->parent->parent->right;
            if (y->color == Red)
            {
                // Case 1, z->parent and y color is Red
                // Change z->parent and y color to Black
                // change z->parent->parent (grandparent) color to Red
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            // if y color is Black
            else
            {
                if (z->parent->right == z)
                {
                    // Case 2, z is right child
                    // left rotate z and z->parent to make z left child
                    z = z->parent;
                    leftRotate(T, z);
                }
                // Case 3, z is left child
                // right rotate grandparent(z) and change color
                z->parent->color = Black;
                z->parent->parent->color = Red;
                rightRotate(T, z->parent->parent);
            }
        }
        else
        {
            // opposite of above
            // y is left uncle(z)
            pNode y = z->parent->parent->left;
            if (y->color == Red)
            {
                // Case 1, z->parent and y color is Red
                // Change z->parent and y color to Black
                // change z->parent->parent (grandparent) color to Red
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            // if y color is Black
            else
            {
                if (z->parent->left == z)
                {
                    // Case 2, z is left child
                    // right rotate z and z->parent to make z right child
                    z = z->parent;
                    rightRotate(T, z);
                }
                // Case 3, z is right child
                // left rotate grandparent(z) and change color
                z->parent->color = Black;
                z->parent->parent->color = Red;
                leftRotate(T, z->parent->parent);
            }
        }
    }
    T.root->color = Black;
}
