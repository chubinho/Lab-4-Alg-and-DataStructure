#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab_4.h"

tree create_node(char *key, double value, tree Nil_node)
{
    tree newNode = (tree)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprinf(stderr, "Memory are allocation\n");
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
        else{
            Node *uncle = z->parent->parent->left;
            if (uncle->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                uncle->color = BLACK;
                z = z->parent->parent   ;
            }
            else{
                if (z == z->parent->left){
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

tree search(RBTree * tree, char *key){
    Node * current = tree->root;
    while (current != tree->NIL && strcmp(key, current->key) != 0){
        if (strcmp(key, current->key) < 0){
            current = current->left;
        }
        else{
            current = current->right;
        }

    }
    return (current == tree->NIL)? NULL: current;
}
