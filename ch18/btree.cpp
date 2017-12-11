#include "btree.h"
#include <iostream>

using namespace std;

// so key moi node co the chua:
// it nhat: T_MIN_DEGREE-1
// nhieu nhat 2*T_MIN_DEGREE-1
const int T_MIN_DEGREE = 3;

void B_Tree_Print(pNode root, int indent)
{
    if (root)
    {
        // print in preorder
        for (int i = 0; i < indent; ++i)
        {
            cout << ' ';
        }
        for (int i = 0; i < root->n; ++i)
        {
            cout << root->key[i] << " ";
        }
        cout << endl;
        if (!root->leaf)
        {
            for (int i = 0; i < root->n + 1; ++i)
            {
                B_Tree_Print(root->children[i], indent + 8);
            }
        }
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

// Create empty B-Tree
void B_Tree_Create(pNode &root)
{
    root = new Node;
    root->n = 0;
    root->leaf = true;
    root->key = NULL;
    root->children = NULL;
}

void B_Tree_DeAllocate(pNode &root)
{
    if (root)
    {
        if (!root->leaf)
        {
            for (int i = 0; i < root->n + 1; ++i)
            {
                B_Tree_DeAllocate(root->children[i]);
            }
            free(root->children);
        }
        free(root->key);
        delete root;
    }
}

pNode B_Tree_Search(pNode root, int k, int &index)
{
    int j = 0;
    while (j < root->n && k > root->key[j])
    {
        ++j;
    }
    // stop when k >= root->key[j] or j == root->n
    if (j < root->n && k == root->key[j])
    {
        index = j;
        return root;
    }
    if (root->leaf)
    {
        return NULL;
    }
    return B_Tree_Search(root->children[j], k, index);
}

// Insert
// Insert in B-Tree is different from insert in BST
// We don't create new node then insert x,
// instead we insert key to existing leaf node
// If leaf node is full(2t-1 keys) we split it
// A tip: we split (if node full) as we go down
// From root, if root full split it
// then split ... to the node
void B_Tree_Split_Child(pNode &father, int i)
{
    // old_son=children(father) ith is full
    // split old_son to old_son and new_son
    // old_son->n: t-1 and new_son->n: t-1
    // the other key make to father
    pNode old_son = father->children[i];
    pNode new_son = new Node;
    new_son->leaf = old_son->leaf;
    new_son->n = T_MIN_DEGREE - 1;
    new_son->key = (int *)malloc(sizeof(int) * new_son->n);
    // copy t-1 largest key from old_son to new_son
    for (int j = 0; j < T_MIN_DEGREE - 1; ++j)
    {
        // new_son->key[0..t-2] and old_son->key[t..2t-2]
        new_son->key[j] = old_son->key[j + T_MIN_DEGREE];
    }
    // old_son is not leaf node so copy children
    if (!old_son->leaf)
    {
        // copy t largest children from y to z
        new_son->children = (pNode *)malloc(sizeof(pNode) * (new_son->n + 1));
        for (int j = 0; j < T_MIN_DEGREE; ++j)
        {
            // new_son->c[0..t-1] and old_son->c[t..2t-1]
            new_son->children[j] = old_son->children[j + T_MIN_DEGREE];
        }
    }
    old_son->n = T_MIN_DEGREE - 1;
    //// increase father's children and father's key
    // move its children to the right
    father->children =
        (pNode *)realloc(father->children, sizeof(pNode) * (father->n + 2));
    for (int j = father->n + 1; j > i + 1; --j)
    {
        father->children[j] = father->children[j - 1];
    }
    father->children[i + 1] = new_son;
    // move its key to the right
    father->key = (int *)realloc(father->key, sizeof(int) * (father->n + 1));
    for (int j = father->n; j > i; --j)
    {
        father->key[j] = father->key[j - 1];
    }
    father->key[i] = old_son->key[T_MIN_DEGREE - 1];
    ++father->n;
    // strip old son's key and children
    old_son->key = (int *)realloc(old_son->key, sizeof(int) * old_son->n);
    if (!old_son->leaf)
    {
        old_son->children = (pNode *)realloc(old_son->children,
                                             sizeof(pNode) * (old_son->n + 1));
    }
}

void B_Tree_Insert(pNode &root, int k)
{
    // root is full, split before do anything
    // only change root 1 time when root is full
    pNode r = root;
    if (r->n == 2 * T_MIN_DEGREE - 1)
    {
        pNode s = new Node;
        root = s;
        s->leaf = false;
        s->n = 0;
        s->key = NULL;
        s->children = (pNode *)malloc(sizeof(pNode) * (1));
        s->children[0] = r;
        B_Tree_Split_Child(s, 0);
        B_Tree_Insert_NonFull(s, k);
    }
    else
    {
        B_Tree_Insert_NonFull(r, k);
    }
}

void B_Tree_Insert_NonFull(pNode &x, int k)
{
    int i = x->n - 1;
    // Chi chen vao nut la
    if (x->leaf)
    {
        x->key = (int *)realloc(x->key, sizeof(int) * (x->n + 1));
        // Giong insertion sort
        while (i >= 0 && k < x->key[i])
        {
            x->key[i + 1] = x->key[i];
            --i;
        }
        x->key[i + 1] = k;
        ++x->n;
    }
    else
    {
        // child ith la con can chen vao
        while (i >= 0 && k < x->key[i])
        {
            --i;
        }
        ++i;
        // children ith is full
        if (x->children[i]->n == 2 * T_MIN_DEGREE - 1)
        {
            B_Tree_Split_Child(x, i);
            // x now have 2 children, which child we should insert k?
            // key:          i
            // children:    i i+1
            if (x->key[i] < k)
            {
                ++i;
            }
        }
        B_Tree_Insert_NonFull(x->children[i], k);
    }
}

// Final delete always occur in the leaf
void B_Tree_Delete(pNode &root, int k)
{
    // case 1: k exist and root is leaf
    if (root->leaf)
    {
        for (int i = 0; i < root->n; ++i)
        {
            // found which key in leaf to be deleted
            if (root->key[i] == k)
            {
                for (int j = i; j < root->n - 1; ++j)
                {
                    root->key[j] = root->key[j + 1];
                }
                root->key =
                    (int *)realloc(root->key, sizeof(int) * (root->n - 1));
                --root->n;
                return;
            }
        }
        cout << k << " don't exist don't delete" << endl;
        return;
    }
    int i = 0;
    while (i < root->n && root->key[i] < k)
    {
        ++i;
    }
    // case 2 k exist but not leaf
    // found k in internal node
    if (i < root->n && root->key[i] == k)
    {
        // key          i
        // children    i i+1
        if (root->children[i]->n >= T_MIN_DEGREE)
        {
            pNode predessor = maximum(root->children[i]);
            root->key[i] = predessor->key[predessor->n];
            B_Tree_Delete(predessor, root->key[i]);
        }
        else if (root->children[i + 1]->n >= T_MIN_DEGREE)
        {
            pNode successor = minimum(root->children[i + 1]);
            root->key[i] = successor->key[0];
            B_Tree_Delete(successor, root->key[i]);
        }
        // left and right of child ith only has t-1 keys (minimum)
        // merge them by delete right and make left contain k and right
        // child
        else
        {
            B_Tree_Merge_Child(root, i);
            B_Tree_Delete(root->children[i], k);
        }
    }
    // case 3 k not exist but may exist in subtree in children ith
    else
    {
        pNode child = root->children[i];
        if (child->n == T_MIN_DEGREE - 1)
        {
            pNode left_sibling = i > 0 ? root->children[i - 1] : NULL;
            pNode right_sibling = i < root->n ? root->children[i + 1] : NULL;
            // one sibling has more than t
            if (left_sibling && left_sibling->n >= T_MIN_DEGREE)
            {
                // move key[i-1] from root to most left of child, replace
                // key[i-1] by most right key of right_sibling
                child->key =
                    (int *)realloc(child->key, sizeof(int) * (child->n + 1));
                for (int j = child->n; j > 0; --j)
                {
                    child->key[j] = child->key[j - 1];
                }
                // move key[i-1] to child
                child->key[0] =
                    root->key[i - 1]; // i-1 because child has left sibling
                if (!child->leaf)
                {
                    child->children = (pNode *)realloc(
                        child->children, sizeof(pNode) * (child->n + 2));
                    for (int j = child->n + 1; j > 0; --j)
                    {
                        child->children[j] = child->children[j - 1];
                    }
                    child->children[0] =
                        left_sibling->children[left_sibling->n];
                }
                ++child->n;
                // replace key[i-1]
                root->key[i - 1] = left_sibling->key[left_sibling->n - 1];
                // resize left_sibling
                left_sibling->key = (int *)realloc(
                    left_sibling, sizeof(int) * (left_sibling->n - 1));
                if (!left_sibling->leaf)
                {
                    left_sibling->children = (pNode *)realloc(
                        left_sibling, sizeof(pNode) * (left_sibling->n));
                }
                --left_sibling->n;
            }
            else if (right_sibling && right_sibling->n >= T_MIN_DEGREE)
            {
                // move key[i] from root to most right of child
                // replace key[i] from root by most left of right_sibling
                child->key =
                    (int *)realloc(child->key, sizeof(int) * (child->n + 1));
                child->key[child->n] = root->key[i];
                if (!child->leaf)
                {
                    child->children = (pNode *)realloc(
                        child->children, sizeof(pNode) * (child->n + 2));
                    child->children[child->n + 1] = right_sibling->children[0];
                }
                ++child->n;
                // replace key[i]
                root->key[i] = right_sibling->key[0];
                // resize right_sibling
                for (int j = 0; j < right_sibling->n - 1; ++j)
                {
                    right_sibling->key[j] = right_sibling->key[j + 1];
                }
                right_sibling->key = (int *)realloc(
                    right_sibling->key, sizeof(int) * (right_sibling->n - 1));
                if (!right_sibling->leaf)
                {
                    for (int j = 0; j < right_sibling->n; ++j)
                    {
                        right_sibling->children[j] =
                            right_sibling->children[j + 1];
                    }
                    right_sibling->children =
                        (pNode *)realloc(right_sibling->children,
                                         sizeof(pNode) * right_sibling->n);
                }
                --right_sibling->n;
            }
            // have siblings at limit t-1 size of key
            else if (left_sibling)
            {
                B_Tree_Merge_Child(root, i - 1);
                child = left_sibling;
            }
            else if (right_sibling)
            {
                B_Tree_Merge_Child(root, i);
            }
        }
        B_Tree_Delete(child, k);
    }
}

void B_Tree_Merge_Child(pNode &father, int i)
{
    // key       i
    // children i i+1
    pNode left_ch = father->children[i];
    pNode right_ch = father->children[i + 1];

    int k = father->key[i];
    // delete k from father
    for (int j = i; j < father->n - 1; ++j)
    {
        father->key[j] = father->key[j + 1];
    }
    father->key = (int *)realloc(father->key, sizeof(int) * (father->n - 1));
    if (!father->leaf)
    {
        for (int j = i + 1; j < father->n; ++j)
        {
            father->children[j] = father->children[j + 1];
        }
        father->children =
            (pNode *)realloc(father->children, sizeof(pNode) * (father->n));
    }
    --father->n;

    // merge left and k and right
    int new_size = left_ch->n + right_ch->n + 1;
    left_ch->key = (int *)realloc(left_ch->key, sizeof(int) * new_size);
    if (!left_ch->leaf)
    {
        left_ch->children =
            (pNode *)realloc(left_ch->children, sizeof(pNode) * (new_size + 1));
    }
    left_ch->key[left_ch->n] = k; // remember to add k
    for (int j = 0; j < right_ch->n; ++j)
    {
        left_ch->key[left_ch->n + 1 + j] = right_ch->key[j];
    }
    if (!left_ch->leaf)
    {
        for (int j = 0; j < right_ch->n; ++j)
        {
            left_ch->children[left_ch->n + 1 + j] = right_ch->children[j];
        }
        left_ch->children[new_size] = right_ch->children[right_ch->n];
    }
    left_ch->n = new_size;

    // free right child memory
    free(right_ch->key);
    if (!right_ch->leaf)
    {
        free(right_ch->children);
    }
    delete right_ch;
    // if father only have k, delete it
    if (father->n == 0)
    {
        if (!father->leaf)
        {
            free(father->children);
        }
        delete father;
        father = left_ch;
    }
}

pNode minimum(pNode root)
{
    pNode r = root;
    while (!r->leaf)
    {
        r = r->children[0];
    }
    return r;
}

pNode maximum(pNode root)
{
    pNode r = root;
    while (!r->leaf)
    {
        // r has r->n + 1 children
        r = r->children[r->n];
    }
    return r;
}