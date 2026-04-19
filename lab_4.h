#ifndef LAB4_H
#define LAB4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct Node
{
    char key[7]; 
    double value;
    Color color;
    struct Node *left, *right, *parent;
} Node, *tree;

typedef struct RBTree
{
    Node *root;
    Node *NIL;
} RBTree;


RBTree *create_tree();
void insert(RBTree *tree, char *key, double value);
void rb_delete(RBTree *tree, Node *z);
Node *search(RBTree *tree, char *key);
void destroy_tree(RBTree *tree, Node *node);


void left_rotate(RBTree *tree, Node *x);
void right_rotate(RBTree *tree, Node *y);
void insert_fixup(RBTree *tree, Node *z);
void delete_fixup(RBTree *tree, Node *x);
void rb_transplant(RBTree *tree, Node *u, Node *v);
Node *tree_minimum(RBTree *tree, Node *x);
void process_commands(RBTree *tree, const char *input_path, const char *output_path);
void print_tree_to_file(RBTree *tree, Node *root, int space, FILE *out);
void print_tree(RBTree *tree, Node *root, int space);

#endif