unsigned char set_bit(unsigned char c, int i){
	unsigned char  mask = 1 << i;
	return mask | c;
}
int is_bit_i_set(unsigned char comp,int i){

	unsigned char mask = 1 << i;
	return mask & comp;
}

// int check_bit(tree *hufftree, unsigned char comp, int index)
// {
// 	while(index >= 0)
// 	{
// 		if(is_bit_i_set(comp,index))
// 		{
// 			if(hufftree != NULL) hufftree = hufftree->right; 
// 		}
// 		else
// 		{
// 			if(hufftree != NULL) hufftree = hufftree->left;
// 		}
// 		index--;
// 	}
	
// 	return (hufftree == NULL);
// }