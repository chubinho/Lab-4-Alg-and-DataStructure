#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab_4.h"


RBTree * create_tree(){
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    if (tree == NULL)
        return NULL;

    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = BLACK;
    tree->NIL->left = NULL;
    tree->NIL->right = NULL;
    tree->NIL->parent = NULL;
    strcpy(tree->NIL->key, "NIL");
    tree->root = tree->NIL;
    return tree;
}


tree create_node(char *key, double value, tree Nil_node)
{
    tree newNode = (tree)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory are allocation\n");
        exit(1);
    }
    strncpy(newNode->key, key, 6);
    newNode->key[6] = '\0';

    newNode->value = value;
    newNode->color = RED;

    newNode->left = Nil_node;
    newNode->right = Nil_node;
    newNode->parent = Nil_node;

    return newNode;
}

void print_tree(RBTree *tree, Node *root, int space)
{
    if (root == tree->NIL)
        return;

    space += 10;
    print_tree(tree, root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s(%s)\n", root->key, root->color == RED ? "R" : "B");

    print_tree(tree, root->left, space);
}

void left_rotate(RBTree *tree, Node *x)
{
    Node *y = x->right;

    x->right = y->left;
    if (y->left != tree->NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->NIL)
    {
        tree->root = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else if (x->parent->right == x)
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(RBTree *tree, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->NIL)
    {
        tree->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    y->parent = x;
    x->right = y;
}

void insert_fixup(RBTree *tree, Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *uncle = z->parent->parent->right;
            if (uncle->color == RED)
            {
                uncle->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        }
        else
        {
            Node *uncle = z->parent->parent->left;
            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                uncle->color = BLACK;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

tree search(RBTree *tree, char *key)
{
    Node *current = tree->root;
    while (current != tree->NIL && strcmp(key, current->key) != 0)
    {
        if (strcmp(key, current->key) < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return (current == tree->NIL) ? NULL : current;
}

void insert(RBTree *tree, char *key, double value)
{
    Node *z = (Node *)malloc(sizeof(Node));
    if (z == NULL)
    {
        return;
    }
    z->value = value;
    strncpy(z->key, key, 6);
    z->key[6] = '\0';
    z->left = tree->NIL;
    z->right = tree->NIL;
    z->color = RED;

    Node *y = tree->NIL;
    Node *x = tree->root;

    while (x != tree->NIL)
    {
        y = x;
        if (strcmp(z->key, x->key) < 0)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == tree->NIL)
    {
        tree->root = z;
    }
    else if (strcmp(z->key, y->key) < 0)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    insert_fixup(tree, z);
}

void free_nodes(RBTree *tree, Node *node)
{
    if (node != tree->NIL)
    {
        free_nodes(tree, node->left);
        free_nodes(tree, node->right);
        free(node);
    }
}

void destroy_tree(RBTree *tree, Node* node)
{
    if (node != tree->NIL)
    {
        destroy_tree(tree, node->left);
        destroy_tree(tree, node->right);
        free(node);
    }
    if (node == tree->root)
    {
        free(tree->NIL);
        free(tree);
    }
}

void print_tree_to_file(RBTree *tree, Node *root, int space, FILE *out)
{
    if (root == tree->NIL)
    {
        return;
    }

    space += 10;
    print_tree_to_file(tree, root->right, space, out);

    fprintf(out, "\n");
    for (int i = 10; i < space; i++)
    {
        fprintf(out, " ");
    }
    fprintf(out, "%s(%s)\n", root->key, root->color == RED ? "R" : "B");

    print_tree_to_file(tree, root->left, space, out);
}