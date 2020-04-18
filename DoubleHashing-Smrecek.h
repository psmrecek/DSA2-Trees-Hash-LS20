#ifndef DH_HEADER_FILE
#define DH_HEADER_FILE

int Primes[10];
int* createHashTable(int size);
int doubleHash1(int key, int size);
int doubleHash2(int key, int size);
int doubleCompress(int key, int size, int iter, int indexH1, int indexH2);
int* doubleInsert(int* hashTable, int key, int* size, int* count);
int* doubleResize(int** hashTable, int size, int* newSize, int* count);
int* autoInsert(int* hashTable, int key, int* size, int* count);
int doubleSearch(int* hashTable, int key, int size);

#endif