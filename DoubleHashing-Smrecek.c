#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "DoubleHashing-Smrecek.h"

Primes[] = { 13, 113, 1013, 10037, 100043, 1000037, 10000103, 100000049, 1000000033 };

int* createHashTable(int size) {
	int* hashTable = malloc(size * sizeof(int));
	if (hashTable != NULL)
	{
		for (int i = 0; i < size; i++)
			hashTable[i] = -1;
		return hashTable;
	}
}

int doubleHash1(int key, int h1) {
	return (key % h1);
}

int doubleHash2(int key, int h2) {
	return 1 + (key % h2);
}

int doubleCompress(int key, int size, int iter, int indexH1, int indexH2) {
	return (indexH1 + iter * indexH2) % size;
}

int* doubleInsert(int* hashTable, int key, int* size, int* count) {
	int iter = 0;

	int indexH1 = doubleHash1(key, size);
	int indexH2 = doubleHash2(key, size-2);

//	printf("%d %d\n", indexH1, indexH2);

	int indexC = doubleCompress(key, *size, iter++, indexH1, indexH2);

	while (hashTable[indexC] != -1)
	{
		indexC = doubleCompress(key, *size, iter++, indexH1, indexH2);
	}

	hashTable[indexC] = key;
	(*count)++;
	//printf("Kluc %d zapisujem na %d s iteratorom %d, count je %d.\n", key, indexC, --iter, *count);

	return hashTable;
}

int* doubleResize(int* hashTable, int size, int* newSize, int* count) {
//	printf("----------------------\n");

	int* newHashTable = NULL;
	newHashTable = createHashTable(*newSize);

	for (int i = 0; i < size; i++) {
		if (hashTable[i] != -1)
		{
			newHashTable = doubleInsert(newHashTable, hashTable[i], &*newSize, &*count);
		}
	}
	return newHashTable;
}

int* autoInsert(int* hashTable, int key, int* size, int* count) {
	if (*count>*size/2)
	{
//		printf("-------------------------------\n");
		int oldsize = *size;
		int i = 0;
		while (oldsize > Primes[i++]);
		//printf("Nova velkost je %d\n", Primes[i]);
		*size = Primes[i];
		*count = 0;

		//*size *= 2;
		hashTable = doubleResize(hashTable, oldsize, &*size, &*count);
	}
	hashTable = doubleInsert(hashTable, key, &*size, &*count);
	return hashTable;
}

int doubleSearch(int* hashTable, int key, int size) {
	int iter = 0;

	int indexH1 = doubleHash1(key, size);
	int indexH2 = doubleHash2(key, size - 2);
	
	int indexC = doubleCompress(key, size, iter++, indexH1, indexH2);

	while (hashTable[indexC] != -1) {
		if (hashTable[indexC] == key)
		{
			//printf("Kluc %d sa v tabulke nachadza na indexe %d.\n", key, indexC);
			return 1;
		}
		indexC = doubleCompress(key, size, iter++, indexH1, indexH2);
	}
	//printf("Kluc %d sa v tabulke nenachadza.\n", key);
	return 0;
}

int main2() {

	int size = Primes[0];
	int count = 0;

	int* hashTable = createHashTable(size);

	for (int key = 1; key < 600; key++)
	{
		hashTable = autoInsert(hashTable, key, &size, &count);
	}

	doubleSearch(hashTable, 1001, size);
	doubleSearch(hashTable, 1009, size);

	return 0;
}