#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "structs.h"
#include "bit.h"
#include "hash.h"
#include "global.h"

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

void print_pre_order(h_tree *bt)
{	
	if(bt != NULL)
	{
		printf("%c ", bt->c);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}
void main()
{
	char arq_name[300];
	int i;
	
	scanf("%[^\n]s", arq_name);
	FILE *output = fopen(arq_name, "r+b");
	h_tree *tree = NULL;
	if( output == NULL )
	{
		puts("ERRO");
		exit(1);
	}
	rewind(output);
	
	
	//*(last_bit+=fseek(output,-1,SEEK_END))
	
	fseek(output,-1,SEEK_END);
	unsigned char aux_bit=0;
	aux_bit=fgetc(output);
	//printf("%d",aux_bit);
	long long int bytes_arq = ftell(output);
	rewind(output);
	

	unsigned char trash_size=0;
	unsigned short tree_size=0;
	unsigned char c;

	
	//fscanf(output,"%d",&c);
	c=fgetc(output);
	//Obter o tamanho do lixo
	for(i=7;i>=5;i--)
	{
		if(is_bit_i_set(c,i))
		{
			
			trash_size = set_bit(trash_size,7-i);
			c=deset_bit(c,i);
		}

	}


	//Obter o tamanho da arvore
	fscanf(output,"%c",&tree_size);
	for(i=0;i<5;i++)
	{
		if(is_bit_i_set(c,i))
		{
			tree_size+=pow(2,i+8);
		}
	}
	//_________________________________

	tree = montar_arvore(output,tree,tree_size,0);
	//print_pre_order(tree);
	//Criar arquivo com novo nome
	
	FILE* novoarquivo = fopen("novoarquivo.png","w+b");

	//_____
	int j;
	h_tree *raiz = tree;
    
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
		if (ftell(output)==(bytes_arq-1))
		{
			break;
		}
		
	}
    //fscanf(output,"%c",&c);
    
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
}
