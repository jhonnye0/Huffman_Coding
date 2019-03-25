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
		comparisons++;
		tree = create_b_tree(item);		
	}else{
		if(item >= tree->item){
			comparisons++;
			tree->right = insert(tree->right, item);			
		}else{
			comparisons++;
			tree->left = insert(tree->left, item);			
		}
	}
	return tree;
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
	long long int n,size=0;
	printf("num_nodes n_comparisons\n");
	while(scanf("%lld", &n) != EOF)//le a entrada
	{
		tree = insert(tree, n);
		printf("%lld %lld\n",size, comparisons);//imprime no inputabb.txt o tamanho da entrada e o num de comparisons
		size++;//apos n ser adicionado o num de nodes da tree aumenta	
		comparisons=0;
	}

	free_tree(tree);
	return 0;
}