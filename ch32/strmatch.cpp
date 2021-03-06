#include "strmatch.h"
#include <string.h>

// Brute-force
int naiveMatch(const char *T, const char *P)
{
	int n = strlen(T);
	int m = strlen(P);
	for (int i = 0; i <= n - m; ++i) {
		int j;
		for (j = 0; j < m && T[i + j] == P[j]; ++j)
			;
		if (j == m)
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
	for (int i = q - 1, j = k - 2; j >= 0; --i, --j) {
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
	for (int i = 0; i <= m_state; ++i) {
		m_table[i] = new int[m_alphabet];
	}

	for (int q = 0; q <= m_state; ++q) // 0..m state
	{
		for (int c = 0; c < m_alphabet;
		     ++c) // list char in language sigma
		{
			int k = m_state + 1 < q + 2 ? m_state + 1 : q + 2;
			do {
				--k;
			} while (!isSuffix(P, k, q,
					   c)); // end when Pk is suffix Pp'c'
			m_table[q][c] = k;
		}
	}
}

dfaTable::~dfaTable()
{
	for (int i = 0; i <= m_state; ++i) {
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
	dfaTable table(P);

	int state = 0;
	for (int i = 0; i < n; ++i) {
		state = table[state][(int)T[i]];
		if (state == m) // final state
		{
			return i - m + 1;
		}
	}

	return -1;
}

// KMP algorithm
void kmpTable(const char *P, int *pi)
{
	int m = strlen(P);
	pi[0] = 0;
	int q = 0; // point to position need to be compared
	for (int i = 1; i < m; ++i) {
		while (q > 0 && P[q] != P[i]) {
			q = pi[q];
		}
		if (P[q] == P[i]) {
			++q;
		}
		pi[i] = q;
	}
}

int kmpMatch(const char *T, const char *P)
{
	int n = strlen(T);
	int m = strlen(P);

	int *pi = new int[m];
	kmpTable(P, pi);

	int q = 0; // num of char matched in P
	// look like kmpTable but change P[i] -> T[i]
	for (int i = 0; i < n; ++i) {
		while (q > 0 &&
		       P[q] != T[i]) // if not matched, traverse q in pi
		{
			q = pi[q];
		}
		if (P[q] == T[i]) // if matched, increase q
		{
			++q;
		}
		if (q == m) {
			delete[] pi;
			return i - m + 1;
			// q = pi[q];
		}
	}
	delete[] pi;
	return -1;
}

// Thuat toan Horspool
// Dac diem la xet tu phai qua
void hpTable(const char *P, int *shift)
{
	int m = strlen(P);
	for (int i = 0; i < ALPHABET_NUM; ++i) {
		shift[i] = m;
	}
	for (int i = 0; i < m - 1; ++i) {
		// Lay khoang cach tu vi tri phai nhat -> end char
		shift[(int)P[i]] = m - 1 - i;
	}
}

int hpMatch(const char *T, const char *P)
{
	int n = strlen(T);
	int m = strlen(P);

	// Create shift table
	int *shift = new int[ALPHABET_NUM];
	hpTable(P, shift);

	// ABCDABAB
	//  <-A
	// ???A
	int i = m - 1;
	while (i < n) {
		int k = 0;
		while (k < m && P[m - 1 - k] == T[i - k])
			++k;
		if (k == m) {
			delete shift;
			return i - m + 1;
		}

		// Dich con tro dang xet sang phai
		// Hy vong T[i] tiep theo la end char cua P
		i += shift[(int)T[i]];
	}
	delete shift;
	return -1;
}

const char GAP = '?';

int naiveMatchGap(const char *T, const char *P)
{
	int n = strlen(T);
	int m = strlen(P);
	for (int i = 0; i <= n - m; ++i) {
		int j;
		for (j = 0; j < m && (T[i + j] == P[j] || P[j] == GAP); ++j)
			;
		if (j == m)
			return i;
	}
	return -1;
}

// Horspool with gap character
void hpTableGap(const char *P, int *shift)
{
	int m = strlen(P);
	for (int i = 0; i < ALPHABET_NUM; ++i) {
		shift[i] = m;
	}
	int i;
	for (i = m - 1; i >= 0 && P[i] != GAP; --i)
		;
	for (int j = 0; j < m - 1; ++j) {
		if (P[j] != GAP) {
			shift[(int)P[j]] = m - 1 - i;
		}
	}
}

int hpMatchGap(const char *T, const char *P)
{
	int n = strlen(T);
	int m = strlen(P);

	// Create shift table
	int *shift = new int[ALPHABET_NUM];
	hpTableGap(P, shift);

	// ABCDABAB
	//  <-A
	// ???A
	int i = m - 1;
	while (i < n) {
		int k = 0;
		while (k < m &&
		       (P[m - 1 - k] == T[i - k] || P[m - 1 - k] == GAP))
			++k;
		if (k == m) {
			delete shift;
			return i - m + 1;
		}

		// Dich con tro dang xet sang phai
		// Hy vong T[i] tiep theo la end char cua P
		i += shift[(int)T[i]];
	}
	delete shift;
	return -1;
}
