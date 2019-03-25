#include "global.h"

typedef struct element
{
	unsigned char key; //elemento que vem da arvore
	int *path_numofbits; //caminho na arvore
	int tamanho;
	
}element;

typedef struct hash_tree
{
	void *trees[CHAR_SIZE]; //GENERICO...
}hash_tree;

typedef struct h_tree
{
	unsigned char c;
	struct h_tree *left;
	struct h_tree *right;
}h_tree;

typedef struct node
{
	long int f;
	unsigned char c;
	struct node *next;
	struct node *left;
	struct node *right;

}node;

typedef struct snode
{
	int binary;
	struct snode *next;
}snode;

typedef struct stack
{
	int tamanho;
	snode* top;
}stack;

