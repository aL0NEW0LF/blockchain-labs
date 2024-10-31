#include "../include/the_hash.h"

int main() {
    char *hash = hash_string("hello world..");
    
    printf("hash: %s\n", hash);

    brute_force(hash);

    return 0;
}