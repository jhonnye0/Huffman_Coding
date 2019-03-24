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
    
    tree = create_b_tree(item);
  }else{

    if(item >= tree->item){

      tree->right = insert(tree->right, item);
      
    }else{
      tree->left = insert(tree->left, item);
    }
  }
  return tree;
}

b_tree *min_value_node(b_tree *node) 
{ 
  b_tree *current = node; 

  while (current->left != NULL) 
  {
    current = current->left; 
  }
  return current; 
} 

b_tree *delete_node(b_tree *root, int key) 
{ 

  if(root == NULL) 
  {
    comparisons++;
    return root; 
  }

  comparisons++;

  if (key < root->item) 
  { 
    root->left = delete_node(root->left, key); 
  } 
  else if(key > root->item) 
  {
    root->right = delete_node(root->right, key);
  } 
  else 
  {
    if (root->left == NULL) 
    { 
      b_tree *temp = root->right;
      free(root); 
      return temp; 
    } 
    else if (root->right == NULL) 
    { 
      b_tree *temp = root->left; 
      free(root); 
      return temp; 
    } 
    b_tree *temp = min_value_node(root->right); 
    root->item = temp->item;
    root->right = delete_node(root->right, temp->item); 
  }
  return root; 
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
    tree = delete_node(tree, n);
    tree = insert(tree, n);
    printf("%lld %lld\n", size, comparisons);
    comparisons = 0;
    size += 1;
  }
  free_tree(tree);
  return 0;
}
