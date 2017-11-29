#include "bst.h"
#include <iostream>

using namespace std;

pNode getNode(int k)
{
    pNode newNode = new Node;
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Walk
// In BST tree, InOrder print in sorted order
void InOrder(pNode root)
{
    if (root)
    {
        InOrder(root->left);
        cout << root->key << " "; // mid
        InOrder(root->right);
    }
}

void PreOrder(pNode root)
{
    if (root)
    {
        cout << root->key << " "; // before
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void PostOrder(pNode root)
{
    if (root)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key << " "; // after
    }
}

// Search
pNode searchRecursive(pNode root, int k)
{
    // NULL or root
    if (!root || root->key == k)
    {
        return root;
    }
    if (root->key < k)
    {
        return searchRecursive(root->right, k);
    }
    return searchRecursive(root->left, k);
}

pNode searchIterative(pNode root, int k)
{
    pNode r = root;
    while (r && r->key != k)
    {
        if (r->key < k)
        {
            r = r->right;
        }
        else
        {
            r = r->left;
        }
    }
    return r;
}

// min and max
pNode minimum(pNode root)
{
    // min is the most left of BST tree
    pNode r = root;
    while (r && r->left)
    {
        r = r->left;
    }
    return r;
}

pNode maximum(pNode root)
{
    // max is the most right of BST tree
    pNode r = root;
    while (r && r->right)
    {
        r = r->right;
    }
    return r;
}

// successor and predecessor
pNode successor(pNode x)
{
    // successor(x) is the node with the smallest key greater than x
    // if x has right subtree, successor(x) is the min of
    // right subtree
    if (x->right)
    {
        return minimum(x->right);
    }
    // if x has no right subtree, successor(x) is the lowest ancestor(x)
    // whose left child is also an ancestor(x)
    pNode y = x->parent;
    while (y && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

pNode predecessor(x)
{
    // predecessor(x) is the node with the largest key smaller than x
    if (x->left)
    {
        return maximum(x->left);
    }
    // if x has no left subtree, predecessor(x) is the lowest ancestor(x)
    // whose right child is also an ancestor(x)
    pNode y = x->parent;
    while (y && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}
