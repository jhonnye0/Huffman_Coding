
#include <math.h>
#include "global.h"

void put_from_tree(hash_tree *hashtree, unsigned char key, unsigned char comp)
{
	unsigned int index;
	index = key;
	int tam = ceil(log2(comp+1));
	element *new_element = (element*) malloc(sizeof(element));
	new_element->key = key;
	new_element->path_numofbits = (int*) malloc (sizeof(int)*tam);
	int i;
	for(i=0;i<tam;i++)
	{
          if(set_bit(comp,i))
          {
          	new_element->path_numofbits[tam-i-1]=1;
          }
          else
          {
          	new_element->path_numofbits[tam-i-1]=0;
          }
	}
	new_element->tamanho = tam;
	hashtree->trees[index] = new_element;
	
}
void build_hash(node *hufftree, hash_tree *hashtree, unsigned char comp)
{
	if(hufftree == NULL) return;
	else if(hufftree->left == NULL && hufftree->right == NULL)
	{
		put_from_tree(hashtree,hufftree->c,comp);
		return;
	}
	else
	{
		comp = comp << 1;
		build_hash(hufftree->left,hashtree,comp);
		comp = set_bit(comp,0);
		build_hash(hufftree->right,hashtree,comp);
		comp = comp >> 1;
	}
	return;
}