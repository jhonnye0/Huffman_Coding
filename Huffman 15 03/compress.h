//compress file
#include <stdio.h>
#include <string.h>
#include "global.h"
//	   ------------------------------------------
//	   -										-
//	   -										-
//	   -			Comprimindo					-
//	   -										-
//	   -										-
//	   ------------------------------------------
void compress(FILE *input, hash_tree *hash, node *tree, char *arq_name){
	strcat(arq_name, "2");
	FILE *output = fopen(arq_name, "w+b");
	fseek(output, 2, SEEK_SET);
    int i;
    unsigned char c;
    unsigned char aux=0;
    int index = 7;
    
	while(!feof(input))
	{
		c = fgetc(input);
		// for(i = 0; i < hash->trees[c]->tamanho; i++)
		// {
  //              if(hash->trees[c]->path_numofbits[i]==1)
  //              {
  //              	   set_bit(aux,0);
  //              }
  //              index--;
  //              aux = aux << 1;

  //              	if (index == 0 )
  //              	{
  //              		fputc(aux,output);
  //              		aux = 0;
  //              		index = 7;
  //              	}

		// }
	}
	int trash = index;
}