#ifndef lab_4
#define lab_4
typedef enum
{
    RED,
    BLACK
} NodeColor;

typedef struct Node
{
    char key[7];
    double value;

    struct Node *left;
    struct Node *right;
    struct Node *root;
    struct Node *parent;
    NodeColor color;
} Node;

typedef Node *tree;

typedef struct
{
    Node *root;
    Node *NIL;

} RBTree;

#endif