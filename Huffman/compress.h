//compress file
#include <stdio.h>
#include <string.h>
#include "global.h"

// void sethuff(char *arq_name, char *arq_huff){

// }

void compress(FILE *input, hash_tree *hash, node *tree, char *arq_name){
	strcat(arq_name, ".huff");
	FILE *output = fopen(arq_name, "w+b");
	fseek(output, 2, SEEK_SET);

}
