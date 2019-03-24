#include <math.h>
#include "global.h"

//bora
void pop(stack *stackzinha) 
{
	if(stackzinha->top==NULL)
	{
		return;
	}
	stackzinha->tamanho--;
	stackzinha->top = stackzinha->top->next;
}
void push(stack *stackzinha, int letra)
{

	snode *nozinho = (snode*) malloc(sizeof(snode));
	nozinho->binary = letra;
	nozinho->next = stackzinha->top;
	stackzinha->tamanho++;
	stackzinha->top = nozinho;
	
}

void put_from_tree(hash_tree *hashtree, unsigned char key, stack *stacktree)
{
	
	element *new_element = (element*) malloc(sizeof(element));
	new_element->key = key;
	
	new_element->path_numofbits = (int*) malloc (sizeof(int)*stacktree->tamanho);
	int i = stacktree->tamanho;
	snode *aux = stacktree->top;

  
	while(i)
	{
          if(aux->binary==1)
          {
          	new_element->path_numofbits[i-1]=1;
          }
          else
          {
          	new_element->path_numofbits[i-1]=0;
          }
          aux=aux->next;
          
          i--;
	}

	
	hashtree->trees[key] = new_element;
	hashtree->trees[key]->tamanho = stacktree->tamanho;
	int j;
	/*puts("");
	printf(" LETRA : %c \n", key);
	for(j=0;j<stacktree->tamanho;j++)
	{
		printf("%d ",hashtree->trees[key]->path_numofbits[j]);
	}
	printf("\n");*/
	
	
}
void build_hash(node *hufftree, hash_tree *hashtree, stack *stacktree)
{
	
    
	if(hufftree == NULL)
	{
		
		pop(stacktree);
		return ;
		
	} 
	else if(hufftree->left == NULL && hufftree->right == NULL)
	{
		put_from_tree(hashtree,hufftree->c,stacktree);
		
	}
	else
	{
		
			push(stacktree,0);
			build_hash(hufftree->left,hashtree,stacktree);
		
		
			push(stacktree,1);
			build_hash(hufftree->right,hashtree,stacktree);
	}

	pop(stacktree);
	return;
}
hash_tree *create_hash()
{
	hash_tree *new_hash = (hash_tree*) malloc(sizeof(hash_tree));
	int i;
	for(i = 0; i < CHAR_SIZE; i++)
	{
		new_hash->trees[i] = NULL;
	}
	return new_hash;
}
stack *criars()
{
    stack* new_node = (stack*) malloc(sizeof(stack));
    new_node->top = NULL;
    new_node->tamanho = 0;
	return new_node;
}