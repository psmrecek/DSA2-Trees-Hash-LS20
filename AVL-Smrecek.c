#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL-Smrecek.h"

// Peter Smrecek

struct NodeAVL
{
	struct NodeAVL* L;
	struct NodeAVL* R;
	int key;
	int height;
	int count;
};

int heightAVL(struct NodeAVL* N) {								// Getter na vysku uzla
	if (N != NULL)
		return N->height;
	return -1;													// Neexistujuci uzol ma vysku -1
}

void setHeightAVL(struct NodeAVL** N) {							// Setter pre vysku uzla, nastavi vacsiu z vysok podstromov + 1
	int left = heightAVL((*N)->L);
	int right = heightAVL((*N)->R);
	(*N)->height = left > right ? left + 1 : right + 1;
}

struct NodeAVL* rightRotAVL(struct NodeAVL* N) {				// Rotacia doprava
	// LL
	struct NodeAVL* newN = N->L;
	N->L = newN->R;
	newN->R = N;

	setHeightAVL(&N);
	setHeightAVL(&newN);

	return newN;
}

struct NodeAVL* leftRotAVL(struct NodeAVL* N) {
	// RR
	struct NodeAVL* newN = N->R;
	N->R = newN->L;
	newN->L = N;

	setHeightAVL(&N);
	setHeightAVL(&newN);
	return newN;
}

struct NodeAVL* leftRightRotAVL(struct NodeAVL* N) {
	// LR
	N->L = leftRotAVL(N->L);
	return rightRotAVL(N);
}

struct NodeAVL* rightLeftRotAVL(struct NodeAVL* N) {
	// RL
	N->R = rightRotAVL(N->R);
	return leftRotAVL(N);
}

struct NodeAVL* insertAVL(struct NodeAVL* N, int key) {
	if (N == NULL) {
		struct NodeAVL* N = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
		N->L = NULL;
		N->R = NULL;
		N->key = key;
		N->height = 0;
		N->count = 1;
		return N;
	}

	if (N->key == key) {
		N->count += 1;
		return N;
	}

	if (key < N->key)
		N->L = insertAVL(N->L, key);
	else
		N->R = insertAVL(N->R, key);

	setHeightAVL(&N);

	int balance = heightAVL(N->L) - heightAVL(N->R);

	if (balance == 2)						// LL a LR 
	{
		if (key < N->L->key)
			return rightRotAVL(N);			// LL
		else
			return leftRightRotAVL(N);		// LR
	}

	if (balance == -2)						// RR a RL
	{
		if (key > N->R->key)
			return leftRotAVL(N);			// RR
		else
			return rightLeftRotAVL(N);		// RL
	}

	return N;
}

struct NodeAVL* searchMaxHeightAVL(struct NodeAVL* N, int* maxHeight) {
	if (N == NULL)
		return N;

	*maxHeight = *maxHeight > N->height ? *maxHeight : N->height;

	return searchMaxHeightAVL(N->L, &*maxHeight);
	return searchMaxHeightAVL(N->R, &*maxHeight);
}

int getMaxHeightAVL(struct NodeAVL* N) {
	int maxHeight = 0;

	N = searchMaxHeightAVL(N, &maxHeight);
	return maxHeight;
}

struct NodeAVL* searchAVL(struct NodeAVL* N, int key) {
	if (N == NULL || N->key == key)
		return N;
	if (key < N->key)
		return searchAVL(N->L, key);
	return searchAVL(N->R, key);
}

void preOrderAVL(struct NodeAVL* N) {		// Preorder vypis (podla prezentacie)
	if (N != NULL)
	{
		printf("%d-%dx ", N->key, N->count);
		preOrderAVL(N->L);
		preOrderAVL(N->R);
	}
}

void inOrderAVL(struct NodeAVL* N) {		// Preorder vypis (podla prezentacie)
	if (N != NULL)
	{
		preOrderAVL(N->L);
		printf("%d-%dx ", N->key, N->count);
		preOrderAVL(N->R);
	}
}

void postOrderAVL(struct NodeAVL* N) {		// Preorder vypis (podla prezentacie)
	if (N != NULL)
	{
		preOrderAVL(N->L);
		preOrderAVL(N->R);
		printf("%d-%dx ", N->key, N->count);
	}
}