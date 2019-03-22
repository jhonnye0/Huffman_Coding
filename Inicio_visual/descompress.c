#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "structs.h"
#include "bit.h"
#include "hash.h"
#include "global.h"
#include <unistd.h>
void decomp();
typedef struct h_tree
{
	unsigned char c;
	struct h_tree *left;
	struct h_tree *right;
}h_tree;

h_tree *create_t_node(unsigned char c, h_tree* left, h_tree* right)
{
	h_tree *new = (h_tree *) malloc(sizeof(h_tree));
	new->c = c;
	new->left = left;
	new->right = right;
	return new;
}

h_tree *montar_arvore(FILE *output, h_tree *h_tree, int tree_size, int cont)
{
	unsigned char c;
	if(cont == tree_size)
		return NULL;
	
	fscanf(output, "%c", &c);
  
	if(c == '\\')
	{
		fscanf(output, "%c", &c);
	
		return create_t_node(c, NULL, NULL);

	}
	else if(c != '*')
	{
		return create_t_node(c, NULL, NULL);
	}
	else if(h_tree == NULL)
	{

		h_tree = create_t_node(c, NULL, NULL);

		h_tree->left = montar_arvore(output, h_tree->left, tree_size, cont+1);
		h_tree->right = montar_arvore(output, h_tree->right, tree_size, cont+1);
	}

	return h_tree;
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
void output_name(char *str, int word_size)
{
	int i;

}
void welcome_output()
{
	system("cls");
	//system("color 02");
	printf("\n\n\a\a BEM");
	sleep(1);
	printf(" \a\aVINDO A INTERFACE!\n\n\n\n\n");

}
void point_output(int qnt){
	printf(" ");
	while(qnt--)
	{
		printf("."); sleep(1); 
	}
	printf("\n");

}
void comand_output()
{

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
     	//comp();
   		break;

   		case 2 :
     	decomp();
   		break;

   		case 4 :
     	exit(1);
   		break;

   		default :
     	puts(" \nComando invalido, por favor, tente novamente\n ");
     	sleep(3);
    }
    system("cls");
}
void print_pre_order(h_tree *tree)
{	
	if(tree != NULL)
	{
    	printf("%c ", tree->c);
    	print_pre_order(tree->left);
    	print_pre_order(tree->right);
	}
}
void inter()
{
	system("cls");
    FILE *inter = fopen("interface.txt","r");	
    unsigned char c;
    system("color 0C");
    while(fread(&c, 1, 1,inter))
    {
        printf("%c",c);
        usleep(8000);
    }
    int j = 12;
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t  Pressione qualquer tecla para continuar");
    getchar();
    fclose(inter);
    system("cls");
}
void load(){
	int i, j;
   for (i = 0; i <= 10; i++)
   {                
      //printf ("\r  %d%%", i);      
      printf ("  %d%%\r", i * 10);
      fflush (stdout);                      
      for (j = 0; j < i * 5; j++)
      {
         if (!j) // Da espaco na barra pra nao enconstar na borda da tela
           printf (" ");
           
         printf ("%c", 219);
         usleep(4000);
      }                  	
   } 
   printf (" 100%%");
   sleep (2);
}
void decomp(){
	int comando;
	system("cls");
	getchar();
	char arq_name[MAX];
	char format_str[FORMAT_SIZE];
	int i;
	printf(" Digite o nome do arquivo no formato arquivo.huff: \n\n\n ");
	scanf("%[^\n]s", arq_name);
	printf("\n\n\n Digite o formato de saida do arquivo (ex ""mp3""): \n\n\n ");
	scanf("\n%[^\n]s", format_str);
	system("cls");
	FILE *output = fopen(arq_name, "r+b");
	h_tree *tree = NULL;
	if(output == NULL)
	{
		puts("Arquivo invalido, tente novamente");
		sleep(2);
		decomp();
	}
	printf("\n\n\n Iniciando compressao \n");
	sleep(1);
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
	trash_size = trash_calc(&c);
	//Obter o tamanho da arvore
	fscanf(output,"%c", &tree_size);
	for(i=0; i<5; i++)
	{
		if(is_bit_i_set(c,i))
		{
			tree_size += pow(2,i+8);
		}
	}
	//_________________________________

	tree = montar_arvore(output,tree,tree_size,0);
	printf("\n\n\n \aMontando arvore huffman... \n");
	sleep(2);
	//print_pre_order(tree);
	//Criar arquivo com novo nome
	char output_str[STR_SIZE];
	strcpy(output_str, "arquivo_descomprimido.");
	strcat(output_str, format_str);
	FILE* novoarquivo = fopen(output_str,"w+b");

	//_____
	int j;
	h_tree *raiz = tree;
    printf("\n\n\n \aManipulando arquivo \n\n ");
    sleep(2);
    long long int changer = 0;
	while(1)
	{
		fscanf(output,"%c",&c);
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
		if(changer%99999 == 0 && changer <= 5000000)
		{
			printf ("%c", 219);
		}
		if (ftell(output)==(bytes_arq-1))
		{
			break;
		}
		changer += 1;

	}

    //fscanf(output,"%c",&c);
    printf("\n\n\n \aFinalizando arquivo \n\n");
    load();
	for(j=7;j>=trash_size;j--)
		{
           if(is_bit_i_set(aux_bit,j))
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
	printf("\n\n ARQUIVO DESCOMPRIMIDO COM SUCESSO\n\n Escolha sua proxima acao:\n\n");
	puts(" 1. Verificar arvore huffman do arquivo\n");
	puts(" 2. Abrir arquivo\n");
	puts(" 3. Voltar ao inicio\n");
	printf(" 4. Sair do programa\n ");
	scanf("%d", &comando);
	getchar();
	switch (comando)
	{
   		case 1 :
   		system("cls");
   		printf("Arvore do arquivo atual:\n\n");
     	print_pre_order(raiz);
     	printf(" \n\n\n\n Pressione Enter para sair");
     	getchar();
     	printf("\n");
   		break;

   		case 3 :
   		puts(" Voltando a Raiz do programa...");
   		sleep(1);
   		break;

   		default :
     	puts(" \nComando invalido, voltando ao inicio do aplicativo\n ");
     	sleep(3);
    }

}
void main()
{
	inter();
	welcome_output();
	while(1)
	{
		comand_output();
	}
}
