#include "structs.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "bit.h"
#include "hash.h"
#include "global.h"
#include "compress.h"

typedef struct h_tree
{
	unsigned char c;
	struct h_tree *left;
	struct h_tree *right;
}h_tree;

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

node *add(node *head, unsigned char c, int f, node *l, node *r)
{
	node *new = create_node(c, f, l, r);
	if(head != NULL)
	{
		node *current = head;
		node *previous = NULL;
		while(current != NULL && current->f < f)
		{
			previous = current;
			current = current->next;
		}
		if(previous == NULL)
		{
			new->next = current;
			current = new;
			return current;
		}
		else
		{
			previous->next = new;
			new->next = current;
			return head;			
		}
	}
	return new;
}

node *make_tree(node *head)
{
	node *aux1, *aux2; // Crio dois nodes auxiliares

	aux1 = head; // Aponta para o primeiro(menor_f).
	aux2 = head->next; // Aponta para o segundo(menor_f).
	head = head->next->next; // Head vira o terceiro menor da lista

	head = add(head,'*', aux1->f + aux2->f, aux1, aux2);
	return head;
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

stack *criars(){
    stack* new_node=(stack*)malloc(sizeof(stack));
    new_node->top=NULL;
    new_node->tamanho=0;
	return new_node;
}

h_tree *create_t_node(unsigned char c, h_tree* left, h_tree* right)
{
	h_tree *new = (h_tree *) malloc(sizeof(h_tree));
	new->c = c;
	new->left = left;
	new->right = right;
	return new;
}
