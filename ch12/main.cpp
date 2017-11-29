// Binary Search Tree
// All the nodes in left subtree < root < in right
#include "bst.h"
#include <iostream>

using namespace std;

int main()
{
    pNode root = NULL;
    insertion(root, 1);
    insertion(root, 2);
    insertion(root, -1);
    insertion(root, 5);
    insertion(root, -3);
    insertion(root, 7);
    insertion(root, 6);
    insertion(root, 4);
    printPreOrder(root, 0);

    deletion(root, 1);
    printPreOrder(root, 0);

    deletion(root, 5);
    printPreOrder(root, 0);

    deletion(root, 6);
    printPreOrder(root, 0);

    delPostOder(root);
    return 0;
}
