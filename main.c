#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "RBHeader.h"


int* getArray(int seed, int number, int min, int max) {
	int* Arr = (int*)malloc(number * sizeof(int));
	srand(seed);
	for (int i = 0; i < number; i++)
		Arr[i] = (rand() % (max - min + 1)) + min;
	return Arr;
}

void printArray(int* Array, int number) {
	for (int i = 0; i < number; i++)
		printf("%d ", Array[i]);
	printf("\n");
}

struct NodeAVL* AVLtestInsert(int* Array, int number) {
	struct NodeAVL* root = NULL;
	for (int i = 0; i < number; i++)
		root = insertAVL(root, Array[i]);
	return root;
}

void RBtestInsert(int* Array, int number) {
	NILL_RB = malloc(sizeof(struct node));
	NILL_RB->color = BLACK;
	ROOT_RB = NILL_RB;
	for (int i = 0; i < number; i++)
		red_black_insert(Array[i]);
}

void test(int number, int seed, int min, int max) {
	int* Array = getArray(seed, number, min, max);

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	clock_t AVL;
	AVL = clock();

	struct NodeAVL* rootAVL = AVLtestInsert(Array, number);

	AVL = clock() - AVL;
	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	double timeAVL = ((double)AVL) / CLOCKS_PER_SEC;
	printf("Vlozit %d prvkov do AVL stromu trvalo %f sekund.\n", number, timeAVL);
	printf("%f\n", interval);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	clock_t RB;
	RB = clock();
	RBtestInsert(Array, number);
	RB = clock() - RB;
	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	double timeRB = ((double)RB) / CLOCKS_PER_SEC;
	printf("Vlozit %d prvkov do Red-Black stromu trvalo %f sekund.\n", number, timeRB);
	printf("%f\n", interval);

	free(Array);
	printf("----------------------\n");
}

int main() {
	int seed = 11;
	int min = 1;
	int max = INT_MAX;
//	int number = 100000;

	test(1000, seed, min, max);
	test(10000, seed, min, max);
	test(100000, seed, min, max);
	test(1000000, seed, min, max);

//	printArray(Array, number);

	

//	tree_print(ROOT_RB);

//	printf("\nPreorder\n");
//	preOrderAVL(root);
	printf("\n");

	
	return 0;
}