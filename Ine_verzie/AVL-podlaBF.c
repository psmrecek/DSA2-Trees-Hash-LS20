//#include <stdio.h>
//
//// Peter Smrecek
//
//struct Node
//{
//	struct Node* p;
//	struct Node* L;
//	struct Node* R;
//	int key;
//	signed char fac;
//};
//
//int max(int n1, int n2) {
//	if (n1 > n2)
//		return n1;
//	return n2;
//}
//
//int min(int n1, int n2) {
//	if (n1 < n2)
//		return n1;
//	return n2;
//}
//
//int heightAVL(struct Node* N) {
//	if (N == NULL)						// Ak neexistuje, vrati 0
//		return 0;
//
//	int left = heightAVL(N->L);			// Rekurzivne vyrata vysku laveho podstromu
//	int right = heightAVL(N->R);		// Rekurzivne vyrata vysku praveho podstromu
//
//	return max(left, right) + 1;		// Vrati vacsie cislo a prirata 1
//}
//
//int balanceFactorAVL(struct Node* N) {
//	return heightAVL(N->L) - heightAVL(N->R);
//}
//
//struct Node* rightRotAVL(struct Node* N) {
//	// Left Left
//	struct Node* newN = N->L;
//	newN->p = N->p;
//	N->p = newN;
//
//	N->L = newN->R;
//	N->L->p = N->L;
//
//	newN->R = N;
//
//	N->fac += -1 - max(0, newN->fac);
//	newN->fac += -1 + min(0, N->fac);
//
//	return newN;
//}
//
//struct Node* leftRotAVL(struct Node* N) {
//	// Right Right
//	struct Node* newN = N->R;
//	newN->p = N->p;
//	N->p = newN;
//
//	N->R = newN->L;
//	N->R->p = N->R;
//
//	newN->L = N;
//
//	N->fac += 1 - min(0, newN->fac);
//	newN->fac += 1 + max(0, N->fac);
//
//	return newN;
//}
//
//struct Node* recursion(struct Node* N, int key){
//	if (N == NULL) {
//		struct Node* N = (struct Node*)malloc(sizeof(struct Node));
//		N->p = NULL;
//		N->L = NULL;
//		N->R = NULL;
//		N->key = key;
//		N->fac = 0;
//		return N;
//	}
//	struct Node* childL = NULL, * childR = NULL;
//	if (key < N->key) {
//		childL = recursion(N->L, key);
//		//printf("ChildL = %d\n", childL->key);
//		N->L = childL;
//		childL->p = N;
//	}
//	else if (key > N->key) {
//		childR = recursion(N->R, key);
//		//printf("ChildR = %d\n", childR->key);
//		N->R = childR;
//		childR->p = N;
//	}
//	else
//		return N;
//
//	N->fac = balanceFactorAVL(N);
//
//	return N;
//	//// Left Left Case 
//	//if (N->fac > 1 && key < N->L->key)
//	//	return rightRotAVL(N);
//
//	//// Right Right Case 
//	//if (N->fac < -1 && key > N->R->key)
//	//	return leftRotAVL(N);
//
//	//// Left Right Case 
//	//if (N->fac > 1 && key > N->L->key)
//	//{
//	//	N->L = leftRotAVL(N->L);
//	//	return rightRotAVL(N);
//	//}
//
//	//// Right Left Case 
//	//if (N->fac < -1 && key < N->R->key)
//	//{
//	//	N->R = rightRotAVL(N->R);
//	//	return leftRotAVL(N);
//	//}
//
////	printf("Key %d ma BF %d\n", N->key, N->fac);
//}
//struct Node* insertAVL(struct Node* N, int key) {
//	struct Node* child = (struct Node*)malloc(sizeof(struct Node));
//	N = recursion(N, key);
//	struct Node* parent = child->p;
////	printf("Child %d\n", child->key);
//	//if (parent != NULL)
//	//{
//	//	if (parent->L == NULL)
//	//	{
//	//		parent->fac -= 1;
//	//	}
//	//	if (parent->R == NULL)
//	//	{
//	//		parent->fac += 1;
//	//	}
//	//}
//	return N;
//}
//
//void preOrderAVL(struct Node* N) {		// Preorder vypis (podla prezentacie)
//	if (N != NULL)
//	{
//		printf("%d ", N->key);
//		preOrderAVL(N->L);
//		preOrderAVL(N->R);
//	}
//}
//
//void preOrderAVL2(struct Node* N) {		// Preorder vypis (podla prezentacie)
//	if (N != NULL)
//	{
//		if (N->p == NULL)
//			printf("Kluc %d ma balans %d a nema predka\n", N->key, N->fac);
//		else
//			printf("Kluc %d ma balans %d a predka s klucom %d\n", N->key, N->fac, N->p->key);
//
//		preOrderAVL2(N->L);
//		preOrderAVL2(N->R);
//	}
//}
//
//void rightAVL(struct Node* N) {
//	if (N != NULL)
//	{
//		printf("%d ", N->key);
//		rightAVL(N->R);
//	}
//}
//
//void leftAVL(struct Node* N) {
//	if (N != NULL)
//	{
//		printf("%d ", N->key);
//		leftAVL(N->L);
//	}
//}
//
//int main() {
//	struct Node* root = NULL;
//
//	root = insertAVL(root, 10);
//	printf("---------------\n");
//	root = insertAVL(root, 20);
//	printf("---------------\n");
//	root = insertAVL(root, 30);
//	printf("---------------\n");
//	root = insertAVL(root, 40);
//	printf("---------------\n");
//	root = insertAVL(root, 50);
//	printf("---------------\n");
//	root = insertAVL(root, 25);
//	printf("---------------\n");
//	//root = insertAVL(root, 5);
//	printf("---------------\n");
//	printf("\nPreorder2\n");
//	preOrderAVL2(root);
//
//
//	
////	
////	
////	
//////	
//////	root = insertAVL(root, 35);
////
////	printf("\nPreorder2\n");
////	preOrderAVL2(root);
////
//	printf("\nPreorder\n");
//	preOrderAVL(root);
//
//	//printf("\nRight only\n");
//	//rightAVL(root);
//
//	//printf("\nLeft only\n");
//	//leftAVL(root);
//
//	return 0;
//}