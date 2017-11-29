#ifndef _BST_H
#define _BST_H

typedef struct Node *pNode;
struct Node
{
    int key;
    pNode left;
    pNode right;
    pNode parent;
};

pNode getNode(int k);

// walk O(n)
void InOrder(pNode root);
void PreOrder(pNode root);
void PostOrder(pNode root);

// search O(h) h is height
pNode searchRecursive(pNode root, int k);
pNode searchIterative(pNode root, int k);

// min and max O(h)
pNode minimum(pNode root);
pNode maximum(pNode root);

// successor and predecessor
pNode successor(pNode x);
pNode predecessor(pNode x);

#endif
