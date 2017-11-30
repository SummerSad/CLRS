// Red-black tree is a bst tree with one extra bit: color
// 1. Every node is either red or black
// 2. Root is black
// 3. Leaf (NULL) is black
// 4. If a node is red, both children are black
// 5. For each node, all simple path from the node to descendant leaves
// contain the same number of black nodes
// Single sentinel to represent NULL, its color: black
#include "redblack.h"
#include <iostream>

using namespace std;

int main()
{
    Tree T;
    rbInsert(T, 1);
    rbInsert(T, 2);
    rbInsert(T, 3);
    printPreOrder(T.root, T.NIL, 0);
    rbInsert(T, 4);
    rbInsert(T, 5);
    printPreOrder(T.root, T.NIL, 0);
    delPostOrder(T.root, T.NIL);
    return 0;
}
