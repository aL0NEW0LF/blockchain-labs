#include "../include/sha256.h"
#include <string.h>
#include <stdlib.h>

#ifndef DIGEST_SHA256_H
#define DIGEST_SHA256_H

char *digest_sha256(char *data);
char *get_concat_hash(unsigned char* s1, unsigned char* s2);

#endif   // DIGEST_SHA256_H