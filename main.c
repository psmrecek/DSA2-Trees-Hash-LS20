#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "RBHeader.h"
#include "AVLHeader.h"


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

struct NodeAVL* AVLtestSearch(struct NodeAVL* root, int* Array, int number) {
	struct NodeAVL* N = NULL;
	for (int i = 0; i < number; i++)
		N = searchAVL(root, Array[i]);
	return N;
}

struct node* RBtestSearch(int* Array, int number) {
	struct node* N = NULL;
	for (int i = 0; i < number; i++)
		N = tree_search(Array[i]);
	return N;
}

void testInsertSearch(int number, int seed, int min, int max) {
	int* Array = getArray(seed, number, min, max);

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	struct NodeAVL* rootAVL = AVLtestInsert(Array, number);
	QueryPerformanceCounter(&end);
	double intervalAVLi = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Vlozit %d prvkov do AVL stromu trvalo %f sekund.\n", number, intervalAVLi);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	RBtestInsert(Array, number);
	QueryPerformanceCounter(&end);
	double intervalRBi = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Vlozit %d prvkov do Red-Black stromu trvalo %f sekund.\n", number, intervalRBi);

	printf("----------------------\n");

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	struct NodeAVL* nAVL = AVLtestSearch(rootAVL, Array, number);
	QueryPerformanceCounter(&end);
	double intervalAVLs = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v AVL strome trvalo %f sekund.\n", number, intervalAVLs);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	struct node* nRB = RBtestSearch(Array, number);
	QueryPerformanceCounter(&end);
	double intervalRBs = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v Red-Black strome trvalo %f sekund.\n", number, intervalRBs);

	printf("++++++++++++++++++++++\n\n");

	free(Array);
}



int main() {
	int seed = 11;
	int min = 1;
	int max = INT_MAX;
//	int number = 100000;

	testInsertSearch(1000, seed, min, max);
	testInsertSearch(10000, seed, min, max);
	testInsertSearch(100000, seed, min, max);
	testInsertSearch(1000000, seed, min, max);

	return 0;
}