#include "../include/mtree.h"
#include "../include/blockchain.h"
#include<unistd.h>

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

    blockchain chain;

    construct_empty_blockchain(&chain, 3);

    add_block(&chain, "Block 1");
    add_block(&chain, "Block 2");
    add_block(&chain, "Block 3");
    
    blockchain_test(&chain);

    mine_block(&chain, 3, 2);

    blockchain_test(&chain);

    deconstruct_blockchain(&chain);

    return 0;
}