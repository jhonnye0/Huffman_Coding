

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

void print_pre_order(h_tree *tree)
{	
	if(tree != NULL)
	{
    	printf("%c ", tree->c);
    	print_pre_order(tree->left);
    	print_pre_order(tree->right);
	}
}

void print_lista(node *tree)
{	
	if(tree != NULL)
	{
    	printf("%c ", tree->c);
    	print_lista(tree->left);
    	print_lista(tree->right);
	}
}

h_tree *create_t_node(unsigned char c, h_tree* left, h_tree* right)
{
	h_tree *new = (h_tree *) malloc(sizeof(h_tree));
	new->c = c;
	new->left = left;
	new->right = right;
	return new;
}
node *make_tree(node *head) //comprimir
{
	node *aux1, *aux2; // Crio dois nodes auxiliares

	aux1 = head; // Aponta para o primeiro(menor_f).
	aux2 = head->next; // Aponta para o segundo(menor_f).
	head = head->next->next; // Head vira o terceiro menor da lista

	head = add(head,'*', aux1->f + aux2->f, aux1, aux2);
	return head;
}
h_tree *montar_arvore(FILE *output, h_tree *tree, int tree_size, int cont) //descomprimir
{
	unsigned char c;
	if(cont == tree_size)
		return NULL;
	
	fscanf(output, "%c", &c);
  
	if(c == '\\')
	{
		fscanf(output, "%c", &c);
	
		return create_t_node(c, NULL, NULL);

	}
	else if(c != '*')
	{
		return create_t_node(c, NULL, NULL);
	}
	else if(tree == NULL)
	{

		tree = create_t_node(c, NULL, NULL);

		tree->left = montar_arvore(output, tree->left, tree_size, cont+1);
		tree->right = montar_arvore(output, tree->right, tree_size, cont+1);
	}

	return tree;
}
void makeHuffmanTree(node **head)
{
	if((*head)->next == NULL)
	{
		node *aux = *head;

		*head = add(*head, '*', aux->f, aux, NULL);
	}
	else
	{
		while((*head)->next != NULL)
		{
			//print_list(*head);
			*head = make_tree(*head); 	
			//printf("\n");
		}		
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