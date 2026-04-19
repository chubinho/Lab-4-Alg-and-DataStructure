#include <stdio.h>
#include <string.h>
#include "lab_4.h"

void rb_transplant(RBTree *tree, Node *u, Node *v)
{
    if (u->parent == tree->NIL)
    {
        tree->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node *tree_minimum(RBTree *tree, Node *x)
{
    while (x->left != tree->NIL)
    {
        x = x->left;
    }
    return x;
}

void delete_fixup(RBTree *tree, Node *x)
{
    while (x != tree->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->color = RED;
                    w->left->color = BLACK;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = w->parent->color;
                w->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void rb_delete(RBTree *tree, Node *z)
{
    Node *y = z;
    Node *x;
    int y_original_color = y->color;

    if (z->left == tree->NIL)
    {
        x = z->right;
        rb_transplant(tree, z, z->right);
    }

    else if (z->right == tree->NIL)
    {
        x = z->left;
        rb_transplant(tree, z, z->left);
    }
    else
    {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
    
        if (y->parent == z){
            x->parent = y;
        }
        else{
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
    
    rb_transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
    }
    if (y_original_color == BLACK){
        delete_fixup(tree, x);
    }
    free(z);

}