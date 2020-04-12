#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL-Smrecek.h"

// Peter Smrecek

struct NodeAVL													// Struktura pre prvok AVL stromu
{
	struct NodeAVL* L;											// Smernik na laveho potomka
	struct NodeAVL* R;											// Smrernik na praveho potomka
	int key;													// Ulozeny kluc
	int height;													// Ulozena vyska uzla
	int count;													// Ulozeny pocet vyskytov daneho kluca v strome
};

int heightAVL(struct NodeAVL* N) {								// Getter na vysku uzla
	if (N != NULL)
		return N->height;
	return -1;													// Neexistujuci uzol ma vysku -1
}

void setHeightAVL(struct NodeAVL** N) {							// Setter pre vysku uzla, nastavi vacsiu z vysok podstromov + 1
	int left = heightAVL((*N)->L);
	int right = heightAVL((*N)->R);
	(*N)->height = left > right ? left + 1 : right + 1;
}

struct NodeAVL* rightRotAVL(struct NodeAVL* N) {				// Rotacia doprava so zmenami vysok
	// LL
	struct NodeAVL* newN = N->L;
	N->L = newN->R;
	newN->R = N;

	setHeightAVL(&N);
	setHeightAVL(&newN);
	return newN;
}

struct NodeAVL* leftRotAVL(struct NodeAVL* N) {					// Rotacia dolava so zmenami vysok
	// RR
	struct NodeAVL* newN = N->R;
	N->R = newN->L;
	newN->L = N;

	setHeightAVL(&N);
	setHeightAVL(&newN);
	return newN;
}

struct NodeAVL* leftRightRotAVL(struct NodeAVL* N) {			// Rotacia dolava a doprava
	// LR
	N->L = leftRotAVL(N->L);
	return rightRotAVL(N);
}

struct NodeAVL* rightLeftRotAVL(struct NodeAVL* N) {			// Rotacia doprava a dolava
	// RL
	N->R = rightRotAVL(N->R);
	return leftRotAVL(N);
}

struct NodeAVL* balancing(struct NodeAVL** N, int key) {
	int balance = heightAVL((*N)->L) - heightAVL((*N)->R);		// Vypocet balance factoru

	if (balance == 2)							// LL a LR		// AVL umoznuje balance factor iba {-1, 0, 1}, preto ak je 2, kontroluje
	{															// L pripady a rotuje podla potreby
		if (key < (*N)->L->key)
			return rightRotAVL((*N));			// LL
		else
			return leftRightRotAVL((*N));		// LR
	}

	if (balance == -2)							// RR a RL		// Ak je balance -2, kontroluje R pripady a rotuje podla potreby
	{
		if (key > (*N)->R->key)
			return leftRotAVL((*N));			// RR
		else
			return rightLeftRotAVL((*N));		// RL
	}
	return (*N);
}
	

struct NodeAVL* insertAVL(struct NodeAVL* N, int key) {			// Rekurzivna funkcia na vlozenie noveho prvku do stromu
	if (N == NULL) {											// Ak je vstupny smernik na strukturu prazdny, tak ju alokuje
		struct NodeAVL* N = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
		N->L = NULL;
		N->R = NULL;
		N->key = key;
		N->height = 0;
		N->count = 1;
		return N;
	}

	if (N->key == key) {										// Ak sa uz dany kluc v strome nachadza, inkrementuje jeho pocet
		N->count += 1;
		return N;
	}

	if (key < N->key)											// Rekurzivny prechod cez strom smerom k pozadovanemu miestu vlozenia prvku
		N->L = insertAVL(N->L, key);
	else
		N->R = insertAVL(N->R, key);

	setHeightAVL(&N);											// Nastavenie novej vysky uzla

	return balancing(&N, key);
}

struct NodeAVL* searchAVLiter(struct NodeAVL* N, int key) {	// Iterativna funkcia pre vyhladavanie
	while (N != NULL && N->key != key)
		if (key < N->key)
			N = N->L;
		else
			N = N->R;
	return N;
}

struct NodeAVL* searchAVL(struct NodeAVL* N, int key) {		// Rekurzivna funkcia na najdenie prvku v strome
	if (N == NULL || N->key == key)
		return N;
	if (key < N->key)
		return searchAVL(N->L, key);
	return searchAVL(N->R, key);
}

void inOrderAVL(struct NodeAVL* N) {							// Ineorder rekurzivny vypis (podla prezentacie)
	if (N != NULL)
	{
		preOrderAVL(N->L);
		printf("%d-%dx ", N->key, N->count);
		preOrderAVL(N->R);
	}
}

void postOrderAVL(struct NodeAVL* N) {							// Postorder rekurzivny vypis (podla prezentacie)
	if (N != NULL)
	{
		preOrderAVL(N->L);
		preOrderAVL(N->R);
		printf("%d-%dx ", N->key, N->count);
	}
}

void preOrderAVL(struct NodeAVL* N) {							// Preorder rekurzivny vypis (podla prezentacie)
	if (N != NULL)
	{
		printf("%d-%dx ", N->key, N->count);
		preOrderAVL(N->L);
		preOrderAVL(N->R);
	}
}
