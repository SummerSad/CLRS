#ifndef _RED_BLACK_H
#define _RED_BLACK_H

enum Colors
{
    Black,
    Red
};

typedef struct Node *pNode;
struct Node
{
    int key;
    pNode left;
    pNode right;
    pNode parent;
    Colors color;
};

struct Tree
{
    pNode root;
    pNode NIL;
    Tree();
};

pNode getNode(int k, Colors color, pNode NIL);

// rotate
void leftRotate(Tree &T, pNode x);
void rightRotate(Tree &T, pNode x);

// insert
void rbInsert(Tree &T, int k);
void rbInsertFixUp(Tree &T, int k);

#endif
