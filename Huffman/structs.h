#define CHAR_SIZE 257

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
	unsigned char path_numofbits;//caminho na arvore
}element;

typedef struct hash_tree
{
	element *trees[CHAR_SIZE];
}hash_tree;
