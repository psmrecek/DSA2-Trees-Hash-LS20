#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Peter Smrecek

struct Node
{
	struct Node* L;
	struct Node* R;
	int key;
	int height;
};

//int max(int n1, int n2) {
//	if (n1 > n2)
//		return n1;
//	return n2;
//}
//
//int heightAVLrec(struct Node* N) {
//	if (N == NULL)												// Ak neexistuje, vrati 0
//		return 0;
//
//	int left = heightAVLrec(N->L);								// Rekurzivne vyrata vysku laveho podstromu
//	int right = heightAVLrec(N->R);								// Rekurzivne vyrata vysku praveho podstromu
//
//	return max(left, right) + 1;								// Vrati vacsie cislo a prirata 1
//}
//
//int balanceFactorAVLrec(struct Node* N) {						// Rata balance factor cez rekurzivnu funkciu
//	return heightAVLrec(N->L) - heightAVLrec(N->R);
//}

int height(struct Node* N) {									// Getter na vysku uzla
	if (N != NULL)
		return N->height;
	return -1;													// Neexistujuci uzol ma vysku -1
}

void setHeight(struct Node** N) {								// Setter pre vysku uzla, nastavi vacsiu z vysok podstromov
	(*N)->height = height((*N)->L) > height((*N)->R) ? height((*N)->L) + 1 : height((*N)->R) + 1;
}

struct Node* rightRotAVL(struct Node* N) {						// Rotacia doprava
	// LL
	struct Node* newN = N->L;
	N->L = newN->R;
	newN->R = N;

	//N->height = heightAVLrec(N);
	//newN->height = heightAVLrec(newN);
	
	setHeight(&N);
	setHeight(&newN);

	return newN;
}

struct Node* leftRotAVL(struct Node* N) {
	// RR
	struct Node* newN = N->R;
	N->R = newN->L;
	newN->L = N;

	//N->height = heightAVLrec(N);
	//newN->height = heightAVLrec(newN);

	setHeight(&N);
	setHeight(&newN);
	return newN;
}

struct Node* leftRightRotAVL(struct Node* N) {
	// LR
	N->L = leftRotAVL(N->L);
	return rightRotAVL(N);
}

struct Node* rightLeftRotAVL(struct Node* N) {
	// RL
	N->R = rightRotAVL(N->R);
	return leftRotAVL(N);
}

struct Node* insertAVL(struct Node* N, int key) {
	if (N == NULL) {
		struct Node* N = (struct Node*)malloc(sizeof(struct Node));
		N->L = NULL;
		N->R = NULL;
		N->key = key;
		N->height = 0;
		return N;
	}
	
	if (N->key == key)
		return N;

	if (key < N->key)
		N->L = insertAVL(N->L, key);
	else
		N->R = insertAVL(N->R, key);

	setHeight(&N);
	int balance = height(N->L) - height(N->R);

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


	//// Left Left Case 
	//if (balance > 1 && key < N->L->key)
	//	return rightRotAVL(N);

	//// Right Right Case 
	//if (balance < -1 && key > N->R->key)
	//	return leftRotAVL(N);

	//// Left Right Case 
	//if (balance > 1 && key > N->L->key)
	//{
	//	N->L = leftRotAVL(N->L);
	//	return rightRotAVL(N);
	//}

	//// Right Left Case 
	//if (balance < -1 && key < N->R->key)
	//{
	//	N->R = rightRotAVL(N->R);
	//	return leftRotAVL(N);
	//}


	return N;
}

void preOrderAVL(struct Node* N) {		// Preorder vypis (podla prezentacie)
	if (N != NULL)
	{
		printf("%d ", N->key);
		preOrderAVL(N->L);
		preOrderAVL(N->R);
	}
}

void preOrderAVL2(struct Node* N) {		// Preorder vypis (podla prezentacie)
	if (N != NULL)
	{
//		printf("Kluc %d ma balans %d a ma vysku %d\n", N->key, balanceFactorAVLrec(N), N->height);
		printf("Kluc %d ma vysku %d\n", N->key, N->height);
		preOrderAVL2(N->L);
		preOrderAVL2(N->R);
	}
}

void rightAVL(struct Node* N) {
	if (N != NULL)
	{
		printf("%d ", N->key);
		rightAVL(N->R);
	}
}

void leftAVL(struct Node* N) {
	if (N != NULL)
	{
		printf("%d ", N->key);
		leftAVL(N->L);
	}
}

int main() {
	struct Node* root = NULL;

	int seed = 11;
	int min = 1;
	int max = 11;
	int lenght = 10;

	srand(seed);
	max++;
	for (int i = 0; i < lenght; i++)
	{
		int k = (rand() % (max - min)) + min;
		printf("%d ", k);
		root = insertAVL(root, k);
	}

	//root = insertAVL(root, 10);
	//root = insertAVL(root, 20);
	//root = insertAVL(root, 25);
	//root = insertAVL(root, 30);
	//root = insertAVL(root, 40);
	//root = insertAVL(root, 50);
	//root = insertAVL(root, 25);

	printf("\n---------------\n");
	printf("\nPreorder2\n");
	preOrderAVL2(root);

	printf("\nPreorder\n");
	preOrderAVL(root);

	return 0;
}