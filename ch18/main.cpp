// B-Tree
// node x has x.n: size of key x has
// x.key_1 <= .. <= x.key_n (nondecreasing order)
// x.leaf bool
// n + 1 children, k_i <= x.key_i <= k_i+1

#include "btree.h"
#include <iostream>
using namespace std;

int main()
{
    pNode root;
    B_Tree_Create(root);
    const int MAX_TEST = 23;
    for (int i = 0; i < MAX_TEST; ++i)
    {
        B_Tree_Insert(root, i);
    }
    B_Tree_Print(root, 0);

    B_Tree_Delete(root, 0);
    B_Tree_Print(root, 0);

    B_Tree_DeAllocate(root);
    return 0;
}