
#include "global.h"

node *create_node(unsigned char data, int freq, node* left, node* right)
{
	node *new = (node *) malloc(sizeof(node));
	new->f = freq;
	new->c = data;
	new->next = NULL;
	new->left = left;
	new->right = right;
	return new;
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