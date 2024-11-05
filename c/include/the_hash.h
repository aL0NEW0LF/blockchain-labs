// custom hash function for strings

#ifndef THE_HASH_H
#define THE_HASH_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

char *string_to_binary(char *s);
char *binary_to_string(char *binary);
void binary_to_alphanumeric(char *hash, char *output);
uint64_t gen_num(char *s);
char *hash_string(char *str);

#endif   // THE_HASH_H