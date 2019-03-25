#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

//#include "F_declare.h"
#include "structs.h"
#include "bit.h"
#include "hash.h"
#include "global.h"
#include "huff_tree.h"
#include "compress.h"
#include "interface.h"

void comand_output();
void freeall(node *head, stack *stacktree);
void start_compress();
void decompress();


void comand_output()
{
  int comando;
  puts(" Para realizar um comando digite o valor correspondente:\n\n\n\n");
  puts(" 1. Comprimir arquivo\n");
  puts(" 2. Descomprimir arquivo.huff\n");
  puts(" 3. Sair do programa\n ");
  printf(" ");scanf("%d", &comando);
  point_output(3);
  switch (comando)
  {
      case 1 :
      start_compress();
      break;

      case 2 :
      decompress();
      break;

      case 3 :
      exit(1);
      break;

      default :
      puts(" \nComando invalido, por favor, tente novamente\n ");
      comand_output();
      sleep(3);
    }
    system("clear");
}

void freeall(node *head, stack *stacktree)
{
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

void start_compress()
{
	invalido: //Go to 
	system("clear");
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

	system("clear"); 
	printf("\n\n\n Salvando frequencia de bytes...\n\n\n ");
	sleep(1);

	node *head = NULL; // para criar a lista..
	int arr[MAX] = {0}; // array de salvar as frequencias
	FrequencyEnqueue(input, arr, &head); 
	makeHuffmanTree(&head);	
	//print_lista(head);

	printf("\n\n\n Criando arvore huffman...\n\n\n ");
	printf("\n\n\n Criando Hash de mapeamento...\n\n\n ");
	sleep(1);

	stack *stacktree = criars();
	hash_tree *hash = create_hash();
	build_hash(head, hash, stacktree);

    printf("\n\n\n Iniciando compressao...\n\n\n ");
	sleep(1);

	rewind(input);
	compress(input, hash, head);

	freeall(head, stacktree);
	eraseHash(hash);
	
	puts(" Saindo do programa em 5 segundos");
	sleep(5);
	point_output(3);
}

int power(int base, int expo)
{
    /* Base condition */
    if(expo == 0)
        return 1;
    else if(expo > 0)
        return base * power(base, expo - 1);
    else
        return 1 / power(base, -expo);
}
void decompress(){
	invalido:
	system("clear");
	char arq_name[300];
	char formato[25];
	int i;
	getchar();
	printf("Digite o nome do arquivo.huff : \n\n ");
	scanf("%[^\n]s", arq_name);
	FILE *output = fopen(arq_name, "r+b");
	printf(" Digite o formato de saida (ex: mp3) : \n\n ");
	getchar();
	scanf("%[^\n]s", formato);
	sleep(2);
	h_tree *tree = NULL;
	if(output == NULL)
	{
		puts(" Arquivo invalido, tente novamente");
		sleep(1);

		goto invalido;
	}
	rewind(output);
	
	fseek(output, -1, SEEK_END);
	unsigned char aux_bit = 0;
	aux_bit = fgetc(output);

	long long int bytes_arq = ftell(output);
	rewind(output);
	
	unsigned char trash_size = 0;
	unsigned short tree_size = 0;///trocou de short pra char
	unsigned char c;

	c = fgetc(output);
	
	system("clear");
	puts(" Obtendo tamanho do lixo...");
	sleep(1);
	for(i = 5; i <= 7; i++)
	{
		if(is_bit_i_set(c,i))
		{
			trash_size = set_bit(trash_size,i%5);
		}
	}

	puts(" Calculando tamanho da arvore...");
	sleep(1);

	fscanf(output,"%c", &tree_size);
	//tree_size
	for(i = 0; i < 5; i++)
	{
		if(is_bit_i_set(c,i))
		{
			tree_size += power(2,i+8);
		}
	}
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
	
	long long int chager = 0; //carregamento

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
