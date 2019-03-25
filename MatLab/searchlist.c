#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node{
	long long int item;
	struct node* next;
}Node;

/*
Node* createLinkedList();
Node* insertNode(Node *node, int item);
void printLinkedList(Node *first);
int isEmpty(node * first);*/

Node* createLinkedList(){
	return NULL;
}

Node* createNode(long long int item){ //insercao na head
	Node* new = (Node*) malloc(sizeof(Node));
	new->item = item;
	new->next = NULL;
	return new;
}

Node *insert(Node *head, long long int item){

	Node *new = createNode(item);
	if(head == NULL) return new;

	if(head != NULL)
	{
		Node *current = head;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
		return head;
	}
}

long long int comparisons=0;

void printLinkedList(Node *first){
	while(first != NULL){
		printf("%lld ",first->item);
		first = first->next;
	}
	printf("\n");
	//return NULL;
}

Node* search(Node* first, long long int item){
	while(first != NULL){
		if(first->item == item){
			//printf("It is here!\n");
			comparisons++;
			return first;
		}
		comparisons++;
		first = first->next;
	}
	//printf("Not found\n");
	return NULL;
}

Node* removenode(Node* first, long long int item){
	Node *previous = NULL;
	Node *current = first;
	while(current != NULL && current->item != item){
		previous = current;
		current = current->next;
	}
	if(current == NULL){
		return first;
	}
	if(previous == NULL){
		first = current->next;
	} else {
		previous->next = current->next;
	}
	free(current);
	return first; //remember it is a recursive method so we have to return first;
}

int isEmpty(Node * first){
	return (first == NULL);
}

Node *free_list(Node *head)
{
	Node *aux = head;
	while(aux != NULL
)	{
		head = head -> next;
		free(aux);
		aux = head;
	}
	return aux
;}

int main(){
	Node* list = createLinkedList();
	long long int n,size=0;
	printf("num_nodes n_comparisons\n");
	while(scanf("%lld", &n) != EOF)//le a entrada
	{
		list = insert(list, n);
		search(list, n);//busca sempre n
		size++;//apos n ser adicionado o num de nodes da list aumenta
		printf("%lld %lld\n",size, comparisons);//imprime no inputabb.txt o tamanho da entrada e o num de comparisons
		comparisons=0;
	}
	list = free_list(list); 

}