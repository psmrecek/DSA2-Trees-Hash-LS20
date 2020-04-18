#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "DoubleHashing-Smrecek.h"

// Peter Smrecek

Primes[10] = {131, 1031, 10061, 100151, 1000081,
	10000121, 100000541, 1000000021, 10000000061 };

// Pole prvocisel pouzivane na vyber velkosti tabulky

int* createHashTable(int size) {						// Alokovanie novej tabulky s pozadovanou velkostou
	int* hashTable = malloc(size * sizeof(int));
	if (hashTable != NULL)
	{
		for (int i = 0; i < size; i++)
			hashTable[i] = -1;
		return hashTable;
	}
	//printf("Pridelenie pamati pre Double hash tabulku zlyhalo.\nNepodarilo sa alokovat dostatocne vela pamati. Koniec programu.\n");
	//exit(0);
}

int doubleHash1(int key, int size) {					// Hashovacia funkcia 1 (prevzata z prezentacie)
	return (key % size);
}

int doubleHash2(int key, int size) {					// Hashovacia funkcia 2 (prevzata z prezentacie)
	return 1 + (key % (size-4));
}

int doubleCompress(int key, int size, int iter, int indexH1, int indexH2) {
	int index = (indexH1 + iter * indexH2) % size;
	//if (index < 0)
	//{
	//	printf("Pozor, nastalo pretecenie!\n");
	//	printf("%d Zlyhal som key %d size %d iter %d indexH1 %d indexH %d\n",index, key, size, iter, indexH1, indexH2);
	//}
	return index;										// Kompresna funkcia (prevzata z prezentacie)
}

int* doubleInsert(int* hashTable, int key, int* size, int* count) {
	int iter = 0;										// Funkcia na vlozenie do tabulky

	int indexH1 = doubleHash1(key, *size);
	int indexH2 = doubleHash2(key, *size);

	int indexC = doubleCompress(key, *size, iter++, indexH1, indexH2);

	while (hashTable[indexC] != -1)
	{
		indexC = doubleCompress(key, *size, iter++, indexH1, indexH2);
	}

	hashTable[indexC] = key;
	(*count)++;

	return hashTable;
}

int* doubleResize(int** hashTable, int size, int* newSize, int* count) {
	int* newHashTable = NULL;							// Funkcia na zvacsenie tabulky
	newHashTable = createHashTable(*newSize);

	for (int i = 0; i < size; i++) {
		if ((*hashTable)[i] != -1)
		{
			newHashTable = doubleInsert(newHashTable, (*hashTable)[i], &*newSize, &*count);
		}
	}
	free((*hashTable));
	return newHashTable;
}

int* autoInsert(int* hashTable, int key, int* size, int* count) {
	if (*count>*size/2)									// Riadiaca funkcia na vlozenie prvku do tabulky so zmenou velkosti tabulky
	{
		int oldsize = *size;
		int i = 0;
		while (oldsize > Primes[i++]);
		*size = Primes[i];
		*count = 0;
		hashTable = doubleResize(&hashTable, oldsize, &*size, &*count);
	}
	hashTable = doubleInsert(hashTable, key, &*size, &*count);
	return hashTable;
}

int doubleSearch(int* hashTable, int key, int size) {
	int iter = 0;										// Funkcia na prehladavanie hashovacej tabulky 

	int indexH1 = doubleHash1(key, size);
	int indexH2 = doubleHash2(key, size);
	
	int indexC = doubleCompress(key, size, iter++, indexH1, indexH2);

	while (hashTable[indexC] != -1) {
		if (hashTable[indexC] == key)
		{
			return indexC;
		}
		indexC = doubleCompress(key, size, iter++, indexH1, indexH2);
	}
	return -1;
}
