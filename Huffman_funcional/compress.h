#include <stdio.h>
#include <string.h>
#include <math.h>
#include "global.h"
//     ------------------------------------------
//     -                    -
//     -                    -
//     -      Comprimindo         -
//     -                    -
//     -                    -
//     ------------------------------------------
void print_pre_order1(node *bt,unsigned short *aux2)
{ 
  if(bt != NULL)
  {
    if((bt->c == '\\' || bt->c=='*') && bt->right==NULL && bt->left==NULL )
    {
      *aux2+=1;
    }
    *aux2+=1;
    
    print_pre_order1(bt->left,aux2);
    print_pre_order1(bt->right,aux2);
  }
}
void print_pre_order2(node *bt,FILE* output)
{ 
  if(bt != NULL)
  {
    if((bt->c=='*' || bt->c=='\\') && bt->left==NULL && bt->right==NULL)
    {
      fputc('\\',output);
    }

    fputc(bt->c,output);
    print_pre_order2(bt->left,output);
    print_pre_order2(bt->right,output);
  }
}
void compress(FILE *input, hash_tree *hash, node *tree, char *arq_name){
  int tamanho = strlen(arq_name);
  //char arq_name_new[300];
  
  
  //tamanho-=3;
  //arq_name[strlen(arq_name)-4]='\0';
  int i, j;
  
  for(i=0;i<tamanho;i++)
  {
    //arq_name_new[i]=arq_name[i];
  }
  //arq_name[i]='\0';

  strcat(arq_name,".huff");
  /*for(;i<strlen(arq_name)+1;i++)
  {
      arq_name_new[i]=huff[i];
  }*/
  unsigned short tamanhotree = 0;
  print_pre_order1(tree,&tamanhotree);
  //printf("%d",tamanhotree);
  //strcpy(arq_name, arq_name_new);
  
  FILE *output = fopen("a.huff", "w+b");
  
  fseek(output,2+(tamanhotree),SEEK_SET);
 
  //fseek(output, 2, SEEK_SET); 
  
  unsigned char c=0;
  unsigned char aux = 0;
  int index = 7;
  

  
  while(fscanf(input,"%c",&c)!=EOF)
  {

    for(i = 0; i < hash->trees[c]->tamanho; i++)
    {   
      if(hash->trees[c]->path_numofbits[i] == 1)
      {
        aux = set_bit(aux,index);
      }
      index--;
      if(index == -1)
      {
          //printf("%s ", string);
          //fseek(aux,1,SEEK_SET);
        fwrite(&aux,sizeof(unsigned char),1,output);
        aux = 0;
        index = 7;
      }
    }

    
  }
  unsigned short trash = index+1;
  //printf("TRASH : %d\n",trash);
  //fprintf(output,%d,aux);
  //fseek(aux,1,SEEK_SET);
  fwrite(&aux,sizeof(unsigned char),1,output);

  rewind(output);

  
//_______________

  unsigned short aux2 = trash;
  aux2 <<= 13;
  printf("%d\n",tamanhotree);
  aux2+=tamanhotree;
  printf("%d\n",aux2);

  unsigned char byte_1=0;
  unsigned char byte_2=0;

  for(i=15;i>=8;i--)
  {
    if(is_bit_i_set_short(aux2,i))
    {
      
       byte_1 = set_bit(byte_1,i-8);
    }
  }
  for(i=7;i>=0;i--)
  {
    if(is_bit_i_set(aux2,i))
    {
         
       byte_2 = set_bit(byte_2,i);
    }
  }
printf("%d\n",byte_1);
printf("%d\n",byte_2);
fputc(byte_1,output);
fputc(byte_2,output);
print_pre_order2(tree,output);

//______________________________
}
