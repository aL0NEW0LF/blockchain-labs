#include "../include/mtree.h"
#include "../include/blockchain.h"
#include "../include/blockchain-pos.h"
#include <unistd.h>
#include <time.h> 

int main() {
    // compare proof of work and proof of stake
    // proof of work
    printf("Proof of Work ------------------------------------------------------------------------------------\n");
    clock_t t; 
    t = clock(); 
    blockchain chain;

    construct_empty_blockchain(&chain, 3);

    add_block(&chain, "Block 1");
    add_block(&chain, "Block 2");
    add_block(&chain, "Block 3");
    
    blockchain_test(&chain);

    mine_block(&chain, 3, 1);
    mine_block(&chain, 3, 2);
    mine_block(&chain, 3, 3);

    blockchain_test(&chain);

    deconstruct_blockchain(&chain);

    t = clock() - t;
    double time_taken_pow = ((double)t)/CLOCKS_PER_SEC; // in seconds
    
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Proof of Stake ------------------------------------------------------------------------------------\n");

    // proof of stake
    t = clock();

    struct validator validators[3];
    validators[0].username = "Alice";
    validators[0].public_key = digest_sha256("Alice");
    validators[0].stake = 100;

    validators[1].username = "Bob";
    validators[1].public_key = digest_sha256("Bob");
    validators[1].stake = 200;

    validators[2].username = "Charlie";
    validators[2].public_key = digest_sha256("Charlie");
    validators[2].stake = 300;

    blockchain_pos chain_pos;
    construct_empty_blockchain_pos(&chain_pos);

    add_block_pos(&chain_pos, "35", "Dave");
    add_block_pos(&chain_pos, "25", "Eve");
    add_block_pos(&chain_pos, "150", "Faythe");

    blockchain_test_pos(&chain_pos);

    printf("-----------------------------------------\n");

    struct validator chosen_validator = choose_validator(&chain_pos, chain_pos.blocks, validators);

    validate_block_pos(&chain_pos, 1, &chosen_validator);
    validate_block_pos(&chain_pos, 2, &chosen_validator);
    validate_block_pos(&chain_pos, 3, &chosen_validator);

    blockchain_test_pos(&chain_pos);

    printf("-----------------------------------------\n");

    deconstruct_blockchain_pos(&chain_pos);

    t = clock() - t;
    double time_taken_pos = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("---------------------------------------------------------------------------------------------------\n");

    printf("Proof of Work took %f seconds to execute \n", time_taken_pow);
    printf("Proof of Stake took %f seconds to execute \n", time_taken_pos);

    return 0;
}