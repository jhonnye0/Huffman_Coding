#include "global.h"

typedef struct node
{
	int f;
	unsigned char c;
	struct node *next;
	struct node *left;
	struct node *right;

}node;

typedef struct element
{
	unsigned char key;//elemento que vem da arvore
	int *path_numofbits;
	int tamanho;
	//caminho na arvore
}element;

typedef struct hash_tree
{
	element *trees[CHAR_SIZE];
}hash_tree;
