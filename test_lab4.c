#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "lab_4.h"

void test_insert_root()
{
    RBTree *tree = create_tree();
    insert(tree, "key1", 10.5);

    assert(tree->root != tree->NIL);
    assert(strcmp(tree->root->key, "key1") == 0);
    assert(tree->root->color == BLACK); // Корень всегда черный

    destroy_tree(tree, tree->root);
    printf("test_insert_root: OK\n");
}


void test_search()
{
    RBTree *tree = create_tree();
    insert(tree, "abc", 1.0);
    insert(tree, "xyz", 2.0);

    Node *found = search(tree, "abc");
    assert(found != NULL);
    assert(found->value == 1.0);

    Node *not_found = search(tree, "ooo");
    assert(not_found == NULL);

    destroy_tree(tree, tree->root);
    printf("test_search: OK\n");
}


void test_delete_root()
{
    RBTree *tree = create_tree();
    insert(tree, "del", 5.5);

    Node *z = search(tree, "del");
    assert(z != NULL);

    rb_delete(tree, z);
    assert(tree->root == tree->NIL);

    destroy_tree(tree, tree->root);
    printf("test_delete_root: OK\n");
}

void test_key_length()
{
    RBTree *tree = create_tree();
    insert(tree, "123456789", 99.9);

    Node *found = search(tree, "123456");
    assert(found != NULL);
    assert(strlen(found->key) == 6);

    destroy_tree(tree, tree->root);
    printf("test_key_length: OK\n");
}


void test_order()
{
    RBTree *tree = create_tree();
    insert(tree, "m", 50.0);
    insert(tree, "a", 10.0);
    insert(tree, "z", 100.0);

    Node *root = tree->root;
    if (root->left != tree->NIL)
    {
        assert(strcmp(root->left->key, root->key) < 0);
    }
    if (root->right != tree->NIL)
    {
        assert(strcmp(root->right->key, root->key) > 0);
    }

    destroy_tree(tree, tree->root);
    printf("test_order: OK\n");
}

int main()
{
    test_insert_root();
    test_search();
    test_delete_root();
    test_key_length();
    test_order();

    printf("\n--- ALL RB-TREE TESTS PASSED --- \n");
    return 0;
}