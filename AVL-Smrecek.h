#ifndef AVL_HEADER_FILE
#define AVL_HEADER_FILE

int heightAVL(struct NodeAVL* N);
void setHeightAVL(struct NodeAVL** N);
struct NodeAVL* rightRotAVL(struct NodeAVL* N);
struct NodeAVL* leftRotAVL(struct NodeAVL* N);
struct NodeAVL* leftRightRotAVL(struct NodeAVL* N);
struct NodeAVL* rightLeftRotAVL(struct NodeAVL* N);
struct NodeAVL* insertAVL(struct NodeAVL* N, int key);
struct NodeAVL* searchMaxHeightAVL(struct NodeAVL* N, int* maxHeight);
int getMaxHeightAVL(struct NodeAVL* N);
struct NodeAVL* searchAVL(struct NodeAVL* N, int key);
void preOrderAVL(struct NodeAVL* N);
void inOrderAVL(struct NodeAVL* N);
void postOrderAVL(struct NodeAVL* N);

#endif
