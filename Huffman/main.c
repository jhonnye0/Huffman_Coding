#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "structs.h"
#include "bit.h"
#include "hash.h"
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

void print_list(node *head)
{
	node *current = head;
	while(current != NULL)
	{
		printf("%d ", current->f);
		current = current->next;
	}
}

void FrequencyEnqueue(FILE *p, int *arr, node **head)
{
	int i;
	unsigned char c; // caractere para receber o conteudo
	while(fscanf(p, "%c", &c) != EOF)
	{
		arr[c] += 1; // pegando os caracteres
					 // e as freq..
	}
	for (i = 0; i < MAX; ++i) // add na fila de prioridade
	{
		if(arr[i] != 0)
		{
			*head = add(*head, i, arr[i], NULL, NULL); 
		}
	}
}
void makeHuffmanTree(node **head)
{
	while((*head)->next != NULL)
	{
		//print_list(*head);
		*head = make_tree(*head); 	
		//printf("\n");
	}	
	//print_list(*head);
}
void print_pre_order(node *bt)
{	
	if(bt != NULL)
	{
    	printf("%c ", bt->c);
    	print_pre_order(bt->left);
    	print_pre_order(bt->right);
	}
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
int main()
{
	int i;
	node *head = NULL;
	char arq_name[300];
	scanf("%[^\n]s", arq_name);
	FILE *p = fopen(arq_name, "rb");
	if( p == NULL )
	{
		puts("ERRO");
		exit(1);
	}
	int arr[MAX] = {0}; // recebe as freq..
	FrequencyEnqueue(p, arr, &head);
	makeHuffmanTree(&head);	
	puts("");	
	print_pre_order(head);
	//Construir hash;
	hash_tree *hash = create_hash();
	build_hash(head, hash, 0);
	//compress(p, hash, head, arq_name);
	fclose(p);
	return 0;
}
