#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "AVL-Smrecek.h"
#include "RedBlack-prevzate-Smrecek.h"

#include "DoubleHashing-Smrecek.h"
#include "Chaining-prevzate-Smrecek.h"

int* getArray(int number) {
	int* Arr = (int*)malloc(number * sizeof(int));

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
		}
		else
		{
			b = 0;
		}
	}
}

void AVLtestInsertSearch(int number) {
	int* Array = getArray(number);

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

	free(Array);
}

void RBtestInsertSearch(int number) {
	int* Array = getArray(number);

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

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

	free(Array);
}

void DHtestInsertSearch(int number) {
	int* Array = getArray(number);

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

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

	free(Array);
}

void CHtestInsertSearch(int number) {
	int* Array = getArray(number);

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

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

	free(Array);
}

int main() {
	int n = 0;
	
	char choice;

	printf("Vyber testovanu dynamicku mnozinu:\nZvol 'a' pre AVL-Strom\nZvol 'b' pre Red-Black strom"
		"\nZvol 'c' pre Double Hashing tabulku\nZvol 'd' pre Chaining hashovaciu tabulku\n");
	scanf("%c", &choice);
	while (choice<'a' || choice>'d')
	{
		printf("Neplatny vstup!\nVyber testovanu dynamicku mnozinu:\nZvol 'a' pre AVL-Strom\nZvol 'b' pre Red-Black strom"
			"\nZvol 'c' pre Double Hashing tabulku\nZvol 'd' pre Chaining hashovaciu tabulku\n");
		scanf("%c", &choice);
	}

	printf("Vyber pocet vkladov do mnoziny\nZvol '1' pre 100\nZvol '2' pre 1k\nZvol '3' pre 10k\n"
		"Zvol '4' pre 100k\nZvol '5' pre 1m\nZvol '6' pre 10m\nZvol '7' pre 20m\nAlebo napis inu hodnotu manualne\n");

	scanf("%d", &n);
	switch (n)
	{
	case 1:
		n = 100;
		break;
	case 2:
		n = 1000;
		break;
	case 3:
		n = 10000;
		break;
	case 4:
		n = 100000;
		break;
	case 5:
		n = 1000000;
		break;
	case 6:
		n = 10000000;
		break;
	case 7:
		n = 20000000;
		break;
	default: printf("Manualne bolo zvolene cislo %d\n", n);
		break;
	}

	switch (choice)
	{
	case 'a':
		AVLtestInsertSearch(n);
		break;
	case 'b':
		RBtestInsertSearch(n);
		break;
	case 'c':
		DHtestInsertSearch(n);
		break;
	case 'd':
		CHtestInsertSearch(n);
		break;
	default: printf("Neplatny vstup!\n");
		break;
	}

	return 0;
}