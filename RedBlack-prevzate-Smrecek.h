#ifndef RB_HEADER_FILE
#define RB_HEADER_FILE

#define RED 0
#define BLACK 1
								// Kompletne vytvoreny .h subor pre potreby pouzitia implementacie v Testovac.c
struct node {					// Zakomentovane v povodnom subore, presunute do headera aby som mohol pouzivat v Testovac.c
	int key;
	int color;
	struct node* parent;
	struct node* left;
	struct node* right;
};

/* Global, since all function will access them */
struct node* ROOT_RB;			// Obom premennym som pridal _RB aby sa s nicim inym nepomylili
struct node* NILL_RB;

void left_rotate(struct node* x);
void right_rotate(struct node* x);
void tree_print(struct node* x);
void red_black_insert(int key);
void red_black_insert_fixup(struct node* z);
struct node* tree_search(int key);
struct node* tree_minimum(struct node* x);
void red_black_transplant(struct node* u, struct node* v);
void red_black_delete(struct node* z);
void red_black_delete_fixup(struct node* x);

#endif