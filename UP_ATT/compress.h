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

  int i, j;
  strcat(arq_name,".huff");

  unsigned short tamanhotree = 0;
  print_pre_order1(tree,&tamanhotree);

  
  FILE *output = fopen("compactado.huff", "w+b");
  
  fseek(output,2+(tamanhotree),SEEK_SET);
 
 
  
  unsigned char c=0;
  unsigned char aux = 0;
  int index = 7;
  long long int chager = 0; 

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
        fwrite(&aux,sizeof(unsigned char),1,output);
        aux = 0;
        index = 7;
      }
    }
    //load
    if(chager%9999 == 0 && chager <= 9999*75)
      {  
        printf("%c", 219);
      }
    chager += 1;
  }
  puts(" 100%%\n");
  unsigned short trash = index+1;

  fwrite(&aux,sizeof(unsigned char),1,output);

  rewind(output);

  
//_______________
  unsigned short aux2 = trash;
  aux2 <<= 13;
  aux2+=tamanhotree;

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
  //sla
fputc(byte_1,output);
fputc(byte_2,output);
print_pre_order2(tree,output);


fseek(input, 0, SEEK_END);//isso aq buga KKKKKKKKKKKKK
fseek(output, 0, SEEK_END);
long long int in_size = ftell(input);
long long int out_size = ftell(output);
system("cls");
printf("\tArquivo Compactado com sucesso");
printf("\n\n\n\n Tamanho do arquivo antes da compressao %lld KB\n", in_size/1024);
printf(" Tamanho do arquivo apos compressao %lld KB\n", out_size/1024);
sleep(3);
//______________________________
}