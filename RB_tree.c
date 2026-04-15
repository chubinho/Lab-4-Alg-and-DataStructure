#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab_4.h"

tree create_node(char *key, double value, tree Nil_node){
    tree newNode = (tree) malloc(sizeof(Node));
    if (newNode == NULL){
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