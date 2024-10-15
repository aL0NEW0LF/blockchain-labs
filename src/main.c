#include "../include/mtree.h"
#include "../include/digest_sha256.h"

int main() {
    mt_list tree;

    char **transactions = malloc(5 * sizeof(char *));
    for (int i = 0; i < 5; i++) {
        transactions[i] = malloc(32);
    }

    strcpy(transactions[0], "transaction 1");
    strcpy(transactions[1], "transaction 2");
    strcpy(transactions[2], "transaction 3");
    strcpy(transactions[3], "transaction 4");
    strcpy(transactions[4], "transaction 5");
    
    construct_empty_tree(&tree, 5);

    populate_tree(&tree, transactions);

    tree_test(&tree);

    deconstruct_tree(&tree);

    return 0;
}