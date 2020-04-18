#ifndef AVL_HEADER_FILE
#define AVL_HEADER_FILE

//int heightAVL(struct NodeAVL* N);
//void setHeightAVL(struct NodeAVL** N);
struct NodeAVL* rightRotAVL(struct NodeAVL* N);
struct NodeAVL* leftRotAVL(struct NodeAVL* N);
struct NodeAVL* leftRightRotAVL(struct NodeAVL* N);
struct NodeAVL* rightLeftRotAVL(struct NodeAVL* N);
struct NodeAVL* balancing(struct NodeAVL** N, int key);
struct NodeAVL* insertAVL(struct NodeAVL* N, int key);
struct NodeAVL* searchAVLiter(struct NodeAVL* N, int key);
struct NodeAVL* searchAVL(struct NodeAVL* N, int key);
struct NodeAVL* destroyAVL(struct NodeAVL* N);
void preOrderAVL(struct NodeAVL* N);
void inOrderAVL(struct NodeAVL* N);
void postOrderAVL(struct NodeAVL* N);

#endif
