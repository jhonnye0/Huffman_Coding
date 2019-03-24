#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>

#define MAX 256

typedef struct trie{
	int isWord;
	struct trie *suffix[MAX];
}trie;

int haveChildren(trie *current);
int search(trie *head, char *str);
void display(trie *root, char *str, int level);
void insert(trie *head, char *str);
trie *create_node();
trie *delete(trie *root, char *key, int depth);


trie *create_node(){
	trie *new = (trie*) malloc(sizeof(trie));
	new->isWord = 0;	
	int i;
	for(i = 0;i < MAX; i++){
		new->suffix[i] = NULL;
	}
	return new;
}

void insert(trie *head, char *str){
	trie *current = head;
	while(*str){
		if(current->suffix[*str] == NULL){
			current->suffix[*str] = create_node();
		}
		current = current->suffix[*str];
		str++;
	}
	current->isWord = 1;
}

int haveChildren(trie *current){
	int i;
	for(i = 0; i < MAX; i++){
		if(current->suffix[i] != NULL){
			return 1;
		}
	}
	return 0;
}

int search(trie *head, char *str){

	if(head == NULL)
	{
		return 0;
	}		
	trie *current = head;

	//printf("%s\n", str);
	while(*str){
		//printf("%d\n", *str);
		current = current->suffix[*str];
		if(current == NULL){
			return 0;			
		}

		str++;
	}
	return current->isWord;
}
trie *delete(trie *root, char *key, int depth) 
{ 

	if (root == NULL) 
		return NULL; 
	if (depth == strlen(key) ) { 

		if (root->isWord) root->isWord = 0; 

		if (!haveChildren(root)) { 
			free(root); 
			root = NULL; 
		}
		return root; 
	}

	int index = key[depth]; 
	root->suffix[index] = delete(root->suffix[index], key, depth + 1); 

	if (!haveChildren(root) && root->isWord == 0) { 
		free(root); 
		root = NULL; 
	}
	return root; 
} 

void display(trie *root, char *str, int level) 
{ 
	if(root->isWord)  
	{ 
		str[level] = '\0'; 
		printf("%s\n", str);
	} 
	int i; 
	for (i = 0; i < MAX; i++)  
	{ 
		if(root->suffix[i])  
		{ 
			str[level] = i; 
			display(root->suffix[i], str, level + 1); 
		} 
	} 
} 
int main()
{
	trie* root = create_node();
	root->isWord = 1;
	char str[300];
	char aux[300];
	puts("ESCOLHA A OPÇÃO:");
	puts("1) Inserir");
	puts("2) Remover");
	puts("3) Buscar");
	puts("4) EXIT");
	int x, loop = 1;
	
	while(loop)
	{
		scanf("%d", &x);
		getchar();	

		switch(x)
		{
			case 1: // INSERIR -------------------------
			while(1)
			{
				puts("Insira as palavras e digite |0| quando quiser parar.");
				scanf("%s",str);
				getchar();
				if(str[0] == '0')
				{
					break;
				}
				insert(root,str);
			}				
			display(root, aux, 0);
			break;

			case 2: // DELETAR ------------------------
			while(1)
			{
				puts("Digite as palavras que deseja remover e digite |0| quando quiser parar.");
				scanf("%s",str);
				getchar();
				if(str[0] == '0')
				{
					break;
				}
				root = delete(root, str, 0);
			}
			puts("Removida(s) com sucesso!");
			display(root, aux, 0);
			break;

			case 3: // BUSCAR --------------------------
			while(1)
			{
				puts("Digite as palavras que quer buscar e digite |0| quando quiser parar.");
				scanf("%s",str);
				getchar();
				if(str[0] == '0')
				{
					break;
				}
				if(search(root, str)) puts("Palavra encontrada!");
				else puts("Palavra nao encontrada!");
			}
			break;

			case 4: // FINALIZAR --------------------------
			loop = 0;
			puts("FINALIZADO!");
			break;
		}
	}
	return 0;
}

	// 	
	// puts("//////////ESTADO Antes de deletar//////////");
	// display(root, aux, 0);
	// puts("RETIRE PALAVRAS ATE DIGITAR 1");
	// 
	// 
	// puts("//////////ESTADO Depois de deletar//////////");
