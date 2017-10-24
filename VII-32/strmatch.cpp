#include "strmatch.h"
#include <iostream>
#include <string.h>
using namespace std;

// Brute-force
int naiveMatch(const char *T, const char *P)
{
    int n = strlen(T);
    int m = strlen(P);
    for (int i = 0; i <= n - m; ++i)
    {
        bool match = true; // reset for each match
        for (int j = 0; j < m; ++j)
        {
            if (P[j] != T[j + i]) // 1 error is enough
            {
                match = false;
                break;
            }
        }
        if (match == true)
            return i;
    }
    return -1;
}

// Use DFA (Determine Finite Automata)
const int ALPHABET_NUM = 256;
bool isSuffix(const char *P, int k, int q, char a)
{
    // P[0..k-1] is suffix P[0..q-1,a]
    if (k == 0)
        return true;
    if (P[k - 1] != a)
        return false;
    for (int i = q - 1, j = k - 2; j >= 0; --i, --j)
    {
        if (P[i] != P[j])
            return false;
    }
    return true;
}

dfaTable::dfaTable(const char *P)
{
    m_state = strlen(P);
    m_alphabet = ALPHABET_NUM;

    m_table = new int *[m_state + 1];
    for (int i = 0; i <= m_state; ++i)
    {
        m_table[i] = new int[m_alphabet];
    }

    for (int q = 0; q <= m_state; ++q) // 0..m state
    {
        for (int c = 0; c < m_alphabet; ++c) // list char in language sigma
        {
            int k = m_state + 1 < q + 2 ? m_state + 1 : q + 2;
            do
            {
                --k;
            } while (!isSuffix(P, k, q, c)); // end when Pk is suffix Pp'c'
            m_table[q][c] = k;
        }
    }
}

dfaTable::~dfaTable()
{
    for (int i = 0; i <= m_state; ++i)
    {
        delete[] m_table[i];
    }
    delete[] m_table;
}

int *dfaTable::operator[](int i)
{
    return m_table[i];
}

int dfaMatch(const char *T, const char *P)
{
    int n = strlen(T);
    int m = strlen(P);

    // Preprocessor P
    // create table for saving state
    dfaTable table(P);

    int state = 0;
    for (int i = 0; i < n; ++i)
    {
        state = table[state][(int)T[i]];
        if (state == m) // final state
        {
            return i - m + 1;
        }
    }

    return -1;
}
