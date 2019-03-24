#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
//É OBRIGATORIO, O MARCIO PEDIU, cada tad de struct em seu .h
//#include "F_declare.h"
#include "structs.h"
#include "bit.h"
#include "hash.h"
#include "global.h"
#include "huff_tree.h"
#include "compress.h"
//#include "stack.h"
#include "interface.h"


void comp();
void decomp();
void freeall(node *head, stack *stacktree, hash_tree *hash);

void comand_output() //esse aq
{
  system("cls");
  int comando;
  puts(" Para realizar um comando digite o valor correspondente:\n\n\n\n");
  puts(" 1. Comprimir arquivo\n");
  puts(" 2. Descomprimir arquivo.huff\n");
  puts(" 3. Configurar programa\n");
  puts(" 4. Sair do programa\n ");
  printf(" ");scanf("%d", &comando);
  point_output(3);
  switch (comando)
  {
      case 1 :
      comp();

      break;

      case 2 :
      decomp();
      break;

      case 4 :
      exit(1);
      break;

      default :
      puts(" \nComando invalido, por favor, tente novamente\n ");
      comand_output();
      sleep(3);
    }
    system("cls");
}
unsigned char trash_calc(unsigned char *c)
{
	int i;
	int trash_size = 0;
	for(i=7; i>=5; i--)
	{
		if(is_bit_i_set(*c,i))
		{
			trash_size = set_bit(trash_size,7-i);
			*c = reset_bit(*c,i);
		}
	}
	return trash_size;
}
//so p confirmar q to no codigo certo K
// 0kb '-'
void freeall(node *head, stack *stacktree, hash_tree *hash){
	int i;
	node *current = head;
	while(current != NULL)
	{
		free(current);
		head = head->next;
		current = head;
	}
	snode *scurrent = stacktree->top;
	while(scurrent != NULL)
	{
		free(scurrent);
		stacktree->top = stacktree->top->next;
		scurrent = stacktree->top;
	}
	//ss//PQ AGR N TA DANDO MAIS ERRO??????????????????????????
	for(i = 0; i <= CHAR_SIZE; i++)
	{
		if(hash->trees[i] != NULL)
		{
			free(hash->trees[i]);
		}
	}
	free(hash);
	free(stacktree);
}
void comp()
{
	getchar();
	system("cls");
	int i;
	node *head = NULL;
	char arq_name[300];
	stack *stacktree = criars();
	printf("\n\n\n Digite nome de arquivo junto a seu formato (ex ""musica.mp3""): \n\n\n ");
	scanf("%[^\n]s", arq_name);
	FILE *input = fopen(arq_name, "rb");
	//verify
	if(input == NULL)
	{
		puts("Arquivo invalido, tente novamente");
		sleep(1);
		comp();
	}
	int arr[MAX] = {0}; // recebe as freq..
	system("cls");
	printf("\n\n\n Salvando frequencia de bytes...\n\n\n ");
	sleep(1);
	FrequencyEnqueue(input, arr, &head); 
	makeHuffmanTree(&head);	
	printf("\n\n\n Criando arvore huffman...\n\n\n ");
	//hash
	printf("\n\n\n Criando Hash de mapeamento...\n\n\n ");
	sleep(1);
	hash_tree *hash = create_hash();
	build_hash(head, hash, stacktree);
    //compresscall
    printf("\n\n\n Iniciando compressao...\n\n\n ");
	sleep(1);
	rewind(input);
	compress(input, hash, head, arq_name);
	//s, queria entender wtf ALEATORIO DEMAIS
	fclose(input);
	//q old ta dando erro...
	//Descompress de vcs ta dando erro kk
	//freeall(head, stacktree, hash); 

	
}
void decomp(){
	//ta funcionando...
	system("cls");
	char arq_name[300];
	char formato[25];
	int i;
	getchar();
	printf("Digita o nome do arquivo.huff : \n\n");
	scanf("%[^\n]s", arq_name);
	FILE *output = fopen(arq_name, "r+b");
	printf("Digita o nome do formato ex: mp3 : \n\n");
	getchar();
	scanf("%[^\n]s", formato);
	sleep(2);
	h_tree *tree = NULL;
	if( output == NULL )
	{
		puts("ERRO");
		exit(1);
	}
	rewind(output);
	
	fseek(output,-1,SEEK_END);
	unsigned char aux_bit=0;
	aux_bit=fgetc(output);
	//printf("%d",aux_bit);
	long long int bytes_arq = ftell(output);
	rewind(output);
	

	unsigned char trash_size=0;
	unsigned short tree_size=0;
	unsigned char c;
	//posso testar com imagem?
	//fscanf(output,"%d",&c);
	c = fgetc(output);
	//Obter o tamanho do lixo
	puts(" Obtendo tamanho do lixo...");
	sleep(1);
	for(i = 5; i <= 7; i++)
	{
		if(is_bit_i_set(c,i))
		{
			trash_size = set_bit(trash_size,i%5);
			//c = reset_bit(c,i);
		}

	}
	puts(" Calculando tamanho da arvore...");
	sleep(1);
	fscanf(output,"%c",&tree_size);
	for(i=0;i<5;i++)
	{
		if(is_bit_i_set(c,i))
		{
			tree_size += pow(2,i+8);
		}
	}
	//_________________________________
	puts(" Montando arvore...");
	sleep(1);
	tree = montar_arvore(output,tree,tree_size,0);
	char out_str[90];
	strcpy(out_str, "descompactado.");
	strcat(out_str, formato);
	FILE* novoarquivo = fopen(out_str,"w+b");
	int j;
	h_tree *raiz = tree;
    puts(" Relizando descompressão...");
    puts(" Aguarde...");
	sleep(1);
	while(fscanf(output,"%c",&c) != EOF)
	{
		
		if(ftell(output)>=(bytes_arq-1))
		{
			break;
		}
		for(j=7;j>=0;j--)
		{
			
           if(is_bit_i_set(c,j))
           {
           	tree=tree->right;
           }
           else
           {
           	tree=tree->left;
           }
           if(tree->right == NULL && tree->left==NULL)
		   {  
			fputc(tree->c,novoarquivo);
			tree = raiz;
		   }
		}
		
	}
	for(j = 7; j >= trash_size; j--)
		{
           if( is_bit_i_set(aux_bit,j) )
           {
           		tree = tree->right;
           }
           else
           {
           		tree = tree->left;
           }
           if(tree->right == NULL && tree->left==NULL)
		   {  
		    fputc(tree->c,novoarquivo);
			tree = raiz;
		   }
		}
		puts(" Arquivo descomprimido com sucesso");
		sleep(2);
}
void main()
{
	inter();
	welcome_output();
	comand_output();
	
}
