#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab_4.h"

void process_file(RBTree *tree, const char *input_path, const char *output_path)
{
    FILE *in = fopen(input_path, "r");
    FILE *out = fopen(output_path, "w");
    if (!in || !out)
    {
        if (in)
            fclose(in);
        return;
    }

    int op;
    char key[50];
    double val;

    while (fscanf(in, "%d", &op) != EOF)
    {
        switch (op)
        {
        case 1:
            if (fscanf(in, "%s %lf", key, &val) == 2)
            {
                insert(tree, key, val);
                fprintf(out, "1 insert %s %f\n", key, val);
            }
            break;
        case 2:
            if (fscanf(in, "%s", key) == 1)
            {
                Node *z = search(tree, key);
                if (z)
                {
                    rb_delete(tree, z);
                    fprintf(out, "2 delete %s\n", key);
                }
                else
                {
                    fprintf(out, "2 %s\nStatus: Not Found\n", key);
                }
            }
            break;
        case 3:
            fprintf(out, "3 print tree\n Tree Structure:\n");
            print_tree_to_file(tree, tree->root, 0, out);
            fprintf(out," ");
            break;
        case 4:
            if (fscanf(in, "%s", key) == 1)
            {
                Node *res = search(tree, key);
                if (res)
                    fprintf(out, "4 search %s\nResult: Found value %f\n", key, res->value);
                else
                    fprintf(out, "4 %s\nResult: Not Found\n", key);
            }
            break;
        }
    }
    fclose(in);
    fclose(out);
}

void print_menu()
{
    printf("\n--- Red-Black Tree CLI ---\n");
    printf("1. Insert (key value)\n");
    printf("2. Delete (key)\n");
    printf("3. Print Tree\n");
    printf("4. Search (key)\n");
    printf("5. Exit\n");
    printf("Choice: ");
}

int main(int argc, char *argv[])
{
    RBTree *myTree = create_tree();
    if (!myTree)
    {
        return 1;
    }

    if (argc == 3)
    {
        process_file(myTree, argv[1], argv[2]);
    }
    else
    {
        int op;
        char key[50];
        double val;

        while (1)
        {
            print_menu();
            if (scanf("%d", &op) != 1)
                break;

            if (op == 5)
                break;

            switch (op)
            {
            case 1:
                printf("Enter key (max 6 chars) and double value: ");
                if (scanf("%s %lf", key, &val) == 2)
                {
                    if (strlen(key) > 6)
                    {
                        printf("Error: Key too long!\n");
                    }
                    else
                    {
                        insert(myTree, key, val);
                    }
                }
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%s", key);
                Node *to_delete = search(myTree, key);
                if (to_delete)
                {
                    rb_delete(myTree, to_delete);
                    printf("Node deleted.\n");
                }
                else
                {
                    printf("Key not found.\n");
                }
                break;
            case 3:
                printf("\nTree Structure:\n");
                print_tree(myTree, myTree->root, 0);
                break;
            case 4:
                printf("Enter key to search: ");
                scanf("%s", key);
                Node *found = search(myTree, key);
                if (found)
                {
                    printf("Found: %s = %f [%s]\n",
                           found->key, found->value,
                           found->color == RED ? "RED" : "BLACK");
                }
                else
                {
                    printf("Not found.\n");
                }
                break;
            default:
                printf("Invalid operation.\n");
            }
        }
    }

    destroy_tree(myTree, myTree->root);
    return 0;
}