void put_from_tree(hash_tree *hashtree, unsigned char key, unsigned char comp)
{
	unsigned int index;
	index = key;
	element *new_element = (element*) malloc(sizeof(element));
	new_element->key = key;
	new_element->path_numofbits = comp; 
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