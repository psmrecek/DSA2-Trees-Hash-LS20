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
//	int key;
//	int height;
//	int count;
//};
//
////int max(int n1, int n2) {
////	if (n1 > n2)
////		return n1;
////	return n2;
////}
////
////int heightAVLrec(struct Node* N) {
////	if (N == NULL)												// Ak neexistuje, vrati 0
////		return 0;
////
////	int left = heightAVLrec(N->L);								// Rekurzivne vyrata vysku laveho podstromu
////	int right = heightAVLrec(N->R);								// Rekurzivne vyrata vysku praveho podstromu
////
////	return max(left, right) + 1;								// Vrati vacsie cislo a prirata 1
////}
////
////int balanceFactorAVLrec(struct Node* N) {						// Rata balance factor cez rekurzivnu funkciu
////	return heightAVLrec(N->L) - heightAVLrec(N->R);
////}
//
//int heightAVL(struct NodeAVL* N) {									// Getter na vysku uzla
//	if (N != NULL)
//		return N->height;
//	return -1;													// Neexistujuci uzol ma vysku -1
//}
//
//void setHeightAVL(struct NodeAVL** N) {							// Setter pre vysku uzla, nastavi vacsiu z vysok podstromov + 1
//	(*N)->height = heightAVL((*N)->L) > heightAVL((*N)->R) ? heightAVL((*N)->L) + 1 : heightAVL((*N)->R) + 1;
//}
//
//struct NodeAVL* rightRotAVL(struct NodeAVL* N) {				// Rotacia doprava
//	// LL
//	struct NodeAVL* newN = N->L;
//	N->L = newN->R;
//	newN->R = N;
//
//	//N->height = heightAVLrec(N);
//	//newN->height = heightAVLrec(newN);
//	
//	setHeightAVL(&N);
//	setHeightAVL(&newN);
//
//	return newN;
//}
//
//struct NodeAVL* leftRotAVL(struct NodeAVL* N) {
//	// RR
//	struct NodeAVL* newN = N->R;
//	N->R = newN->L;
//	newN->L = N;
//
//	//N->height = heightAVLrec(N);
//	//newN->height = heightAVLrec(newN);
//
//	setHeightAVL(&N);
//	setHeightAVL(&newN);
//	return newN;
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
//		N->key = key;
//		N->height = 0;
//		N->count = 1;
//		return N;
//	}
//	
//	if (N->key == key) {
//		(N->count)++;
//		return N;
//	}
//		
//	if (key < N->key)
//		N->L = insertAVL(N->L, key);
//	else
//		N->R = insertAVL(N->R, key);
//
//	setHeightAVL(&N);
//	int balance = heightAVL(N->L) - heightAVL(N->R);
//
//	if (balance == 2)						// LL a LR 
//	{
//		printf("Do vyrovnania ide %d\n", N->key);
//		if (key < N->L->key)
//			return rightRotAVL(N);			// LL
//		else
//			return leftRightRotAVL(N);		// LR
//	}
//
//	if (balance == -2)						// RR a RL
//	{
//		printf("Do vyrovnania ide %d\n", N->key);
//		if (key > N->R->key)
//			return leftRotAVL(N);			// RR
//		else
//			return rightLeftRotAVL(N);		// RL
//	}
//
//	return N;
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
//		printf("%d-%dx ", N->key, N->count);
//		preOrderAVL(N->L);
//		preOrderAVL(N->R);
//	}
//}
//
//void preOrderAVL2(struct NodeAVL* N) {		// Preorder vypis (podla prezentacie)
//	if (N != NULL)
//	{
////		printf("Kluc %d ma balans %d a ma vysku %d\n", N->key, balanceFactorAVLrec(N), N->height);
//		printf("Kluc %d ma vysku %d\n", N->key, N->height);
//		preOrderAVL2(N->L);
//		preOrderAVL2(N->R);
//	}
//}
//
////void rightAVL(struct Node* N) {
////	if (N != NULL)
////	{
////		printf("%d ", N->key);
////		rightAVL(N->R);
////	}
////}
//
////void leftAVL(struct Node* N) {
////	if (N != NULL)
////	{
////		printf("%d ", N->key);
////		leftAVL(N->L);
////	}
////}
//
//
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
//	//rootAVL = insertAVL(rootAVL, 25);
//	//rootAVL = insertAVL(rootAVL, 30);
//	//rootAVL = insertAVL(rootAVL, 40);
//	//rootAVL = insertAVL(rootAVL, 50);
//	//rootAVL = insertAVL(rootAVL, 25);
//
//
//	//printf("Maximalna vyska stromu je %d\n", getMaxHeightAVL(rootAVL));
//
//	printf("\n---------------\n");
//	printf("\nPreorder2\n");
//	preOrderAVL2(rootAVL);
//
//	//printf("\nPreorder\n");
//	//preOrderAVL(rootAVL);
//
//	return 0;
//}