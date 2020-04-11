//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include "AVLHeader.h"
//
//// Peter Smrecek
//
//struct NodeAVL
//{
//	struct NodeAVL* L;
//	struct NodeAVL* R;
//	struct NodeAVL* Parent;
//	int key;
//	int height;
//	int count;
//};
//
//int heightAVL(struct NodeAVL* N) {								// Getter na vysku uzla
//	if (N != NULL)
//		return N->height;
//	return -1;													// Neexistujuci uzol ma vysku -1
//}
//
//void setHeightAVL(struct NodeAVL** N) {							// Setter pre vysku uzla, nastavi vacsiu z vysok podstromov + 1
//	int left = heightAVL((*N)->L);
//	int right = heightAVL((*N)->R);
//	(*N)->height = left > right ? left + 1 : right + 1;
//}
//
//struct NodeAVL* rightRotAVL(struct NodeAVL* N) {				// Rotacia doprava
//	// LL
//	struct NodeAVL* newN = N->L;
//	N->L = newN->R;
//	newN->R = N;
//
//	setHeightAVL(&N);
//	setHeightAVL(&newN);
//
//	return newN;
//}
//
//struct NodeAVL* leftRotAVL(struct NodeAVL* N) {
//	// RR
//
//	struct NodeAVL* newN = N->R;
//	//N->R = newN->L;
//	//newN->L = N;
//
//	//setHeightAVL(&N);
//	//setHeightAVL(&newN);
//	//return newN;
//}
//
//struct NodeAVL* leftRightRotAVL(struct NodeAVL* N) {
//	// LR
//	N->L = leftRotAVL(N->L);
//	return rightRotAVL(N);
//}
//
//struct NodeAVL* rightLeftRotAVL(struct NodeAVL* N) {
//	// RL
//	N->R = rightRotAVL(N->R);
//	return leftRotAVL(N);
//}
//
//struct NodeAVL* insertAVL(struct NodeAVL* N, int key) {
//	if (N == NULL) {
//		struct NodeAVL* N = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
//		N->L = NULL;
//		N->R = NULL;
//		N->Parent = NULL;
//		N->key = key;
//		N->height = 0;
//		N->count = 1;
//		return N;
//	}
//
//	//if (N->key == key) {
//	//	N->count += 1;
//	//	return N;
//	//}
//
//	struct NodeAVL* X = N;
//	struct NodeAVL* Y = NULL;
//
//	while (X != NULL)
//	{
//		Y = X;
//		if (key == X->key) {
//			(X->count)++;
//			return N;
//		}
//		else if (key < X->key)
//			X = X->L;
//		else
//			X = X->R;
////		printf("Cyklus\n");
//	}
////	printf("%d\n", Y->key);
//
//	if (Y == NULL) {
//		N->key = key;
//	}
//	else if (key < Y->key) {
//		Y->L = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
//		Y->L->L = NULL;
//		Y->L->R = NULL;
//		Y->L->Parent = Y;
//		Y->L->key = key;
//		Y->L->height = 0;
//		(Y->height)++;
//		Y->L->count = 1;
//		printf("%d zapisane dolava od %d\n", key, Y->key);
//	}	
//	else {
//		Y->R = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
//		Y->R->L = NULL;
//		Y->R->R = NULL;
//		Y->R->Parent = Y;
//		Y->R->key = key;
//		Y->R->height = 0;
//		(Y->height)++;
//		Y->R->count = 1;
//		printf("%d zapisane doprava od %d\n", key, Y->key);
//	}
//
//	int balance = heightAVL(Y->L) - heightAVL(Y->R);
//	printf("Vysky Y->%d Y->L->%d Y->R->%d\n", heightAVL(Y), heightAVL(Y->L), heightAVL(Y->R));
//	printf("Balance %d je %d\n", Y->key, balance);
//
//	//if (balance == 2)						// LL a LR 
//	//{
//	//	if (key < Y->L->key) {
//	//		return rightRotAVL(Y->Parent);			// LL
//	//	}	
//	//	else {
//	//		return leftRightRotAVL(Y->Parent);		// LR
//	//	}
//	//		
//	//}
//
//	if (balance == -2)						// RR a RL
//	{
////		printf("%d > %d", key, Y->key);
//		if (key > Y->key) {
//			//printf("%d < %d\n", Y->Parent->key, Y->key);
//			//if (Y->Parent->Parent == NULL)
//			//{
//			//	printf("Zmena root\n");
//			//	leftRotAVL(Y->Parent);
//			//}
//			//else
//			{
//				//leftRotAVL(Y->Parent);		// RR
//			}
//						
//		}
//		else {
//			//return rightLeftRotAVL(Y->Parent);		// RL
//		}
//			
//	}
//
//	return N;
//
//
//	//if (key < N->key)
//	//	N->L = insertAVL(N->L, key);
//	//else
//	//	N->R = insertAVL(N->R, key);
//
//	//setHeightAVL(&N);
//	//int balance = heightAVL(N->L) - heightAVL(N->R);
//
//	//if (balance == 2)						// LL a LR 
//	//{
//	//	if (key < N->L->key)
//	//		return rightRotAVL(N);			// LL
//	//	else
//	//		return leftRightRotAVL(N);		// LR
//	//}
//
//	//if (balance == -2)						// RR a RL
//	//{
//	//	if (key > N->R->key)
//	//		return leftRotAVL(N);			// RR
//	//	else
//	//		return rightLeftRotAVL(N);		// RL
//	//}
//
//	//return N;
//}
//
//struct NodeAVL* searchMaxHeightAVL(struct NodeAVL* N, int* maxHeight) {
//	if (N == NULL)
//		return N;
//	*maxHeight = *maxHeight > N->height ? *maxHeight : N->height;
//	return searchMaxHeightAVL(N->L, &maxHeight);
//	return searchMaxHeightAVL(N->R, &maxHeight);
//}
//
//int getMaxHeightAVL(struct NodeAVL* N) {
//	int maxHeight = 0;
//	N = searchMaxHeightAVL(N, &maxHeight);
//	return maxHeight;
//}
//
//struct NodeAVL* searchAVL(struct NodeAVL* N, int key) {
//	if (N == NULL || N->key == key)
//		return N;
//	if (key < N->key)
//		return searchAVL(N->L, key);
//	return searchAVL(N->R, key);
//}
//
//void preOrderAVL(struct NodeAVL* N) {		// Preorder vypis (podla prezentacie)
//	if (N != NULL)
//	{
//		if (N->Parent != NULL)
//			printf("%d-%dx (%d) H-%d, ", N->key, N->count, N->Parent->key, N->height);
//		else 
//			printf("%d-%dx NULL H-%d, ", N->key, N->count, N->height);
//		
//		preOrderAVL(N->L);
//		preOrderAVL(N->R);
//	}
//}
//
//int main() {
//	struct NodeAVL* rootAVL = NULL;
//
//	int seed = 11;
//	int min = INT_MIN + 100;
//	int max = INT_MAX;
//	int lenght = 10;
//	int s;
//
//	//srand(seed);
//	//for (int i = 0; i < lenght; i++)
//	//{
//	//	int k = (rand() % (max - min + 1)) + min;
//	//	//printf("%d ", k);
//	//	rootAVL = insertAVL(rootAVL, k);
//	//	if (i % 5 == 0)
//	//		s = k;
//	//}
//
//	//struct NodeAVL* najdeny = searchAVL(rootAVL, s);
//	//if (najdeny != NULL && s != NULL)
//	//	printf("\nNajdeny kluc %d\n", najdeny->key);
//
//	
//
//	rootAVL = insertAVL(rootAVL, 10);
//	rootAVL = insertAVL(rootAVL, 20);
//	rootAVL = insertAVL(rootAVL, 25);
//	//rootAVL = insertAVL(rootAVL, 30);
//	//rootAVL = insertAVL(rootAVL, 40);
//	//rootAVL = insertAVL(rootAVL, 50);
//	//rootAVL = insertAVL(rootAVL, 29);
//
//
//	//printf("Maximalna vyska stromu je %d\n", getMaxHeightAVL(rootAVL));
//
//	printf("\nPreorder\n");
//	preOrderAVL(rootAVL);
//
//	return 0;
//}