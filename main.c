#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "AVL-Smrecek.h"
#include "RedBlack-prevzate-Smrecek.h"

#include "DoubleHashing-Smrecek.h"
#include "Chaining-prevzate-Smrecek.h"

int* getArray(int seed, int number, int min, int max) {
	int* Arr = (int*)malloc(number * sizeof(int));

	//srand(seed);
	//for (int i = 0; i < number; i++)
	//	Arr[i] = (rand() % (max - min + 1)) + min;

	for (int i = 0; i < number; i++)
		Arr[i] = i+1;

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

struct NodeAVL* AVLtestSearch(struct NodeAVL* root, int* Array, int number) {
	struct NodeAVL* N = NULL;
	int i;
	for (i = 0; i < number; i++) {
		N = searchAVL(root, Array[i]);
	}
	return root;
}

void RBtestInsert(int* Array, int number) {
	NILL_RB = malloc(sizeof(struct node));
	NILL_RB->color = BLACK;
	ROOT_RB = NILL_RB;
	for (int i = 0; i < number; i++)
		red_black_insert(Array[i]);
}


struct node* RBtestSearch(int* Array, int number) {
	struct node* N = NULL;
	for (int i = 0; i < number; i++)
		N = tree_search(Array[i]);
	return N;
}

int* DoubleHashInsert(int *size, int* Array, int number) {
	*size = Primes[0];
	int count = 0;

	int* hashTable = NULL;
	hashTable = createHashTable(*size);

	for (int i = 0; i < number; i++)
	{
		hashTable = autoInsert(hashTable, Array[i], &*size, &count);
	}
	return hashTable;
}

void DoubleHashSearch(int* hashTable, int size, int* Array, int number) {
	int b;
	for (int i = 0; i < number; i++)
	{
		b = doubleSearch(hashTable, Array[i], size);
	}
}

void HashTableInsert(HashTable* table, int* Array, int number) {
	ht_setup(&*table, sizeof(int), sizeof(int), 10);
	ht_reserve(&*table, 100);
	int x;
	int y = 4;
	for (int i = 0; i < number; i++)
	{
		x = Array[i];
		ht_insert(&*table, &x, &y);
	}
}

void HashTableSearch(HashTable* table, int* Array, int number) {
	int x;
	int b;
	for (int i = 0; i < number; i++)
	{
		x = Array[i];
		if (ht_contains(&*table, &x)) {
			b = 1;
			//printf("Tabulka obsahuje %d\n", x);
			//y = *(int*)ht_lookup(&*table, &x);
			///* Or use convenience macros */
			//y = HT_LOOKUP_AS(int, &table, &x);
			//printf("%d's value is: %d\n", x, y);
		}
		else
		{
			b = 0;
			//printf("ee %d\n", i);
		}
	}
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
	struct NodeAVL* nAVL = AVLtestSearch(rootAVL, Array, number);
	QueryPerformanceCounter(&end);
	double intervalAVLs = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v AVL strome trvalo %f sekund.\n", number, intervalAVLs);

	//printf("Maximalna vyska stromu je %d\n", getMaxHeightAVL(rootAVL));
	//preOrderAVL(rootAVL);
	//printf("\n");

	printf("----------------------\n");

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	RBtestInsert(Array, number);
	QueryPerformanceCounter(&end);
	double intervalRBi = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Vlozit %d prvkov do Red-Black stromu trvalo %f sekund.\n", number, intervalRBi);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	struct node* nRB = RBtestSearch(Array, number);
	QueryPerformanceCounter(&end);
	double intervalRBs = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v Red-Black strome trvalo %f sekund.\n", number, intervalRBs);

	printf("----------------------\n");

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	int sizeHashTable = 0;
	int* DoubleHashTable = DoubleHashInsert(&sizeHashTable, Array, number);
	QueryPerformanceCounter(&end);
	double intervalDoubleHashi = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Vlozit %d prvkov do Double-Hashing tabulky trvalo %f sekund.\n", number, intervalDoubleHashi);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	DoubleHashSearch(DoubleHashTable, sizeHashTable, Array, number);
	QueryPerformanceCounter(&end);
	double intervalDoubleHashs = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v Double-Hashing tabulke trvalo %f sekund.\n", number, intervalDoubleHashs);

	free(DoubleHashTable);

	printf("----------------------\n");

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	HashTable table;
	HashTableInsert(&table, Array, number);
	QueryPerformanceCounter(&end);
	double intervalGitHashI = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Vlozit %d prvkov do prevzatej hash tabulky trvalo %f sekund.\n", number, intervalGitHashI);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	HashTableSearch(&table, Array, number);
	QueryPerformanceCounter(&end);
	double intervalGitHashS = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	printf("Najst %d prvkov v prevzatej hash tabulke trvalo %f sekund.\n", number, intervalGitHashS);


	printf("++++++++++++++++++++++\n\n");


	free(Array);
}

int main() {
	int seed = 11;
//	int seed = time(0);
	int min = 0;
	int max = 100000000;

	//printf("10\n");
	//testInsertSearch(10, seed, min, max);

	//printf("100\n");
	//testInsertSearch(100, seed, min, max);

	//printf("1k\n");
	//testInsertSearch(1000, seed, min, max);

	//printf("10k\n");
	//testInsertSearch(10000, seed, min, max);

	//printf("100k\n");
	//testInsertSearch(100000, seed, min, max);

	//printf("1m\n");
	//testInsertSearch(1000000, seed, min, max);

	printf("10m\n");
	testInsertSearch(10000000, seed, min, max);

	//printf("100m\n");
	//testInsertSearch(100000000, seed, min, max);

	return 0;
}