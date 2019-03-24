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
void freeall(node *head, stack *stacktree);

void comand_output() //esse aq
{
	//BORA LOGO TEM HIFEN?//MDS DEU RUIM
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
void eraseHash(hash_tree *hashTable){
  int i;
  for(i = 0; i < CHAR_SIZE; i++)
  {
  	if(hashTable->trees[i] != NULL)
  	{
  		///VAI SEPARADO MSM, TO NJEM AI
  		free(hashTable->trees[i]->path_numofbits);
   		free(hashTable->trees[i]);
  	}
  }
  free(hashTable);
}
void freeall(node *head, stack *stacktree){
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
	free(stacktree);
}
void comp()
{
	invalido: //goto
	system("cls");
	char arq_name[300];

	printf("\n\n\n Digite nome de arquivo junto a seu formato (ex ""musica.mp3""): \n\n\n ");
	getchar();
	scanf("%[^\n]s", arq_name);

	FILE *input = fopen(arq_name, "rb");
	//verify
	if(input == NULL)
	{
		puts("Arquivo invalido, tente novamente");
		sleep(1);

		goto invalido;
	}
	int i;
	node *head = NULL;
	stack *stacktree = criars();
	int arr[MAX] = {0}; 
	system("cls");

	printf("\n\n\n Salvando frequencia de bytes...\n\n\n ");
	sleep(1);

	FrequencyEnqueue(input, arr, &head); 
	makeHuffmanTree(&head);	
	//print_lista(head);

	printf("\n\n\n Criando arvore huffman...\n\n\n ");
	printf("\n\n\n Criando Hash de mapeamento...\n\n\n ");
	sleep(1);

	hash_tree *hash = create_hash();
	build_hash(head, hash, stacktree);

    printf("\n\n\n Iniciando compressao...\n\n\n ");
	sleep(1);

	rewind(input);
	compress(input, hash, head, arq_name);
	//free
	freeall(head, stacktree);
	eraseHash(hash);
	//DA PRA LER N? KKKKKKKKKKKKKKKKKKKKKK
	puts(" Saindo do programa em 5 segundos");
	sleep(5);
	point_output(3);
}
void decomp(){
	//ta funcionando...
	system("cls");
	char arq_name[300];
	char formato[25];
	int i;
	getchar();
	printf("Digite o nome do arquivo.huff : \n\n ");
	scanf("%[^\n]s", arq_name);
	FILE *output = fopen(arq_name, "r+b");
	printf("Digita o nome do formato de saida (ex: mp3) : \n\n ");
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
	aux_bit = fgetc(output);

	long long int bytes_arq = ftell(output);
	rewind(output);
	

	unsigned char trash_size = 0;
	unsigned short tree_size = 0;
	unsigned char c;

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
    puts(" Relizando descompressao...");
    printf(" Aguarde...\n ");
	sleep(1);
	//carregamento
	long long int chager = 0;
	while(fscanf(output,"%c",&c) != EOF)
	{
		if(ftell(output)>=(bytes_arq))
		{
			break;
		}
		for(j = 7; j >= 0; j--)
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
		if(chager%9999 == 0 && chager <= 9999*75)
		{	
			printf("%c", 219);
		}
		chager += 1; 
	}
	puts(" 100%%");
	//So executar essa vez
	//SÓ? TA LOUCO É DIFICIL VEY
	if(trash_size)
	{
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
	}
	puts(" Arquivo descomprimido com sucesso!");
	puts(" Saindo do programa em 5 segundos");

	sleep(5);
	point_output(3);
}
void main()
{
	inter();
	welcome_output();
	comand_output();
	
}
