#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "AVL-Smrecek.h"
#include "RedBlack-prevzate-Smrecek.h"

#include "DoubleHashing-Smrecek.h"
#include "Chaining-prevzate-Smrecek.h"

void printArray(int* Array, int number) {						// Pomocna funkcia pre kontrolny vypis vygenerovanej postupnosti
    for (int i = 0; i < number; i++)
        printf("%d ", Array[i]);
    printf("\n");
}

int* getArraySequence(int number) {										// Funkcia na generovanie postupnosti cisel od 1 po number+1
    int* Arr = (int*)malloc((number + 12) * sizeof(int));

    for (int i = 0; i < number; i++)
    	Arr[i] = i+1;
    return Arr;
}

int* getArray(int number) {										// Funkcia na generovanie zmiesaneho pola cisiel
    int* Arr = (int*)malloc((number + 12) * sizeof(int));

    int size2 = number / 4 + 3;
    int* arr1 = (int*)malloc(size2 * sizeof(int));
    int* arr2 = (int*)malloc(size2 * sizeof(int));
    int* arr3 = (int*)malloc(size2 * sizeof(int));
    int* arr4 = (int*)malloc(size2 * sizeof(int));

    for (int i = 0; i < size2; i++) {
        arr1[i] = i + 1;
        arr2[i] = i + 10000001;
        arr3[i] = i + 20000001;
        arr4[i] = i + 30000001;
    }

    int j, k, l;
    for (j = 0, k = size2 - 1, l = 0; j < size2, k >= 0, l < size2; j += 4, k--, l++) {
        Arr[j] = arr4[l];
        Arr[j + 1] = arr2[k];
        Arr[j + 2] = arr3[l];
        Arr[j + 3] = arr1[k];
    }

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    return Arr;
}

struct NodeAVL* AVLtestInsert(int* Array, int number) {			// Funkcia vkladajuca prvky postupnosti do AVL stromu
    struct NodeAVL* root = NULL;
    for (int i = 0; i < number; i++)
        root = insertAVL(root, Array[i]);

    return root;
}

struct NodeAVL* AVLtestSearch(struct NodeAVL* root, int* Array, int number) {
    struct NodeAVL* N = NULL;									// Funkcia hladajuca prvky postupnosti v AVL strome
    int i;
    for (i = 0; i < number; i++) {
        N = searchAVL(root, Array[i]);
        if (N == NULL)
        {
            printf("Hladany kluc %d sa v RB strome nenachadza.\n", Array[i]);
        }
    }
    return root;
}

void RBtestInsert(int* Array, int number) {						// Funkcia vkladajuca prvky postupnosti do RB stromu
    NILL_RB = malloc(sizeof(struct node));
    NILL_RB->color = BLACK;
    ROOT_RB = NILL_RB;
    for (int i = 0; i < number; i++)
        red_black_insert(Array[i]);
}


struct node* RBtestSearch(int* Array, int number) {				// Funkcia hladajuca prvky postupnosti v RB strome
    struct node* N = NULL;
    for (int i = 0; i < number; i++) {
        N = tree_search(Array[i]);
        if (N == NULL)
        {
           printf("Hladany kluc %d sa v RB strome nenachadza.\n", Array[i]);
        }
    }
    return N;
}

int* DoubleHashInsert(int* size, int* Array, int number) {		// Funkcia vkladajuca prvky postupnosti do Double hashing tabulky
    *size = Primes[0];
    int count = 0;

    int* hashTable = NULL;
    hashTable = createHashTable(*size);

    for (int i = 0; i < number; i++)
        hashTable = autoInsert(hashTable, Array[i], &*size, &count);

    return hashTable;
}

void DoubleHashSearch(int* hashTable, int size, int* Array, int number) {
    int b;														// Funkcia vyhladavajuca prvky pola v Double hashing tabulke
    for (int i = 0; i < number; i++) {
        b = doubleSearch(hashTable, Array[i], size);
        if (b == -1) printf("Hladany kluc %d sa v Double hash tabulke nenachadza.\n", Array[i]);
    }
}

void HashTableInsert(HashTable* table, int* Array, int number) {
    ht_setup(&*table, sizeof(int), sizeof(int), 10);			// Funkcia vkladajuca prvky postupnosti do Chaining tabulky
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
    int x;														// Funkcia vyhladavajuca prvky pola v Chaining tabulke
    int b;
    for (int i = 0; i < number; i++)
    {
        x = Array[i];
        b = ht_contains(&*table, &x);
        if (b == 0)
            printf("Hladany kluc %d sa v prevzatej tabulke nenachadza.\n", x);   
    }
}

void AVLtestInsertSearch(int* Array, int number) {							// Funkcia na meranie casu pre Insert a Search v AVL
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

    printf("Prebieha uvolnenie pamati AVL, cas tejto operacie sa nemeria.\n");
    destroyAVL(rootAVL);
}

void RBtestInsertSearch(int* Array, int number) {							// Funkcia na meranie casu pre Insert a Search v RB
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

    printf("Uvolenie pamati pre RB strom nie je podporovane.\n");
}

void DHtestInsertSearch(int* Array, int number) {							// Funkcia na meranie casu pre Insert a Search v Double hashing tabulke
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

    printf("Prebieha uvolnenie pamati DH Tabulky, cas tejto operacie sa nemeria.\n");
    free(DoubleHashTable);
}

void CHtestInsertSearch(int* Array, int number) {							// Funkcia na meranie casu pre Insert a Search v Chaining tabulke
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

    printf("Prebieha uvolnenie pamati Chaining tabulky, cas tejto operacie sa nemeria.\n");
    ht_clear(&table);
	ht_destroy(&table);
}

int main() {
    // Samotne testovanie pomocou vyberu z moznosti a nasledneho zavolania prislusnej testovacej funkcie

    int n = 0;
    

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

    int* Array = getArray(n);

    AVLtestInsertSearch(Array, n);
    printf("------------------------\n");
    DHtestInsertSearch(Array, n);
    printf("------------------------\n");
    CHtestInsertSearch(Array, n);
    printf("------------------------\n");
    RBtestInsertSearch(Array, n);
    
    free(Array);

    return 0;
}