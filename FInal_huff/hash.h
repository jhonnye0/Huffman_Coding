#include <math.h>
#include "global.h"


void pop(stack *stackzinha);
void push(stack *stackzinha, int letra);
void put_on_hash(hash_tree *hashtree, unsigned char key, stack *stacktree);
void build_hash(node *hufftree, hash_tree *hashtree, stack *stacktree);
void eraseHash(hash_tree *hashTable);

stack *criars();

hash_tree *create_hash();


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

void put_on_hash(hash_tree *hashtree, unsigned char key, stack *stacktree) // compress
{
	
	element *new_element = (element *) malloc(sizeof(element));
	new_element->key = key;

	new_element->path_numofbits = (int*) malloc (sizeof(int)*stacktree->tamanho);
	int i = stacktree->tamanho;
	snode *aux = stacktree->top;
  
	while(i)
	{
          if(aux->binary == 1)
          {
          	new_element->path_numofbits[i-1] = 1;
          }
          else
          {
          	new_element->path_numofbits[i-1] = 0;
          }
          aux = aux->next;
          i--;
	}
	
	hashtree->trees[key] = new_element;
	((element *)hashtree->trees[key])->tamanho = stacktree->tamanho;
}
void build_hash(node *hufftree, hash_tree *hashtree, stack *stacktree) // compress
{
	if(hufftree == NULL)
	{	
		return;		
	} 

	else if(hufftree->left == NULL && hufftree->right == NULL) // folha
	{
		put_on_hash(hashtree,hufftree->c,stacktree);
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

void eraseHash(hash_tree *hashTable)
{
  int i;
  for(i = 0; i < CHAR_SIZE; i++)
  {
  	if(hashTable->trees[i] != NULL)
  	{
  		
  		free(((element *)hashTable->trees[i])->path_numofbits);
   		free(hashTable->trees[i]);
  	}
  }

  free(hashTable);
}