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
  int i, j;
  unsigned char c;
  unsigned char aux = 0;
  int index = 7;

  while(!feof(input))
	{
		c = fgetc(input);
		if(c == 255) {break;}
		for(i = 0; i < hash->trees[c]->tamanho; i++)
		{   
        if(hash->trees[c]->path_numofbits[i] == 1)
        {
          aux = set_bit(aux,index);
        }
        index--;
        if(index == -1)
        {
          unsigned char string[9];
          for(j = 0; j < 8 ; j++)
          {   
            if(is_bit_i_set(aux,j))
            {
              string[8-j-1] = '1';
            }
            else
            {
              string[8-j-1] = '0';
            }
          } 
          for(j = 0; j < 8; j++)
          {
              fputc(string[j], output);
          }
          //printf("%s ", string);
         // fputs(string,output);
          aux = 0;
          index = 7;
        }
		}
	}
	int trash = index;
}