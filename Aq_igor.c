
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct binary_tree
{
	long long int item;
	struct binary_tree *left;
	struct binary_tree *right;
}b_tree;

b_tree *create_b_tree(long long int item)
{
	b_tree *new_tree = (b_tree *) malloc(sizeof(b_tree));
	new_tree->item = item;
	new_tree->left = new_tree->right = NULL;	
	return new_tree; 
}
b_tree *create_empty_b()
{
	return NULL;
}

long long int comparisons=0;

b_tree *insert(b_tree *tree, long long int item)
{	 
	if(tree == NULL){
		comparisons += 1;
		tree = create_b_tree(item);
	}else{
		if(item >= tree->item){
			comparisons += 1;
			tree->right = insert(tree->right, item);
			
		}else{
			comparisons += 1;
			tree->left = insert(tree->left, item);
		}
	}
	return tree;
}

void busca(b_tree *bt, int item, int *achou) {
    if (bt == NULL) {
    	if(*achou == 0)
    	{
    		comparisons += 1;
    	}
    	return;
    }   
    if(bt->item == item && *achou == 0)
    {
    	comparisons += 1;
    	*achou = 1;
    }
    if(item >= bt->item)
    {
    	if(*achou == 0)
    	{
    		comparisons += 1;
    	}
    	busca(bt->right, item, achou);
    }
    else
    {
   		if(*achou == 0)
    	{
    		comparisons += 1;
    	}
 		busca(bt->left, item, achou);
	}
   
}
void free_tree(b_tree *tree)
{
	if(tree == NULL)
		return;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

int main()
{
	b_tree *tree = create_empty_b();
	long long int n,size = 1;
	printf("num_nodes n_comparisons\n");
	while(scanf("%lld", &n) != EOF)//le a entrada
	{
		int achou = 0;
		tree = insert(tree, n);
		printf("Tamanho/Comp de insert %lld %lld\n",size, comparisons);//imprime no inputabb.txt o tamanho da entrada e o num de comparisons
		comparisons = 0;
		busca(tree, n, &achou);
		printf("Comp de Search %lld\n", comparisons);
		comparisons = 0;
		size += 1;
	}
	free_tree(tree);
	return 0;
}
