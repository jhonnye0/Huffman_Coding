unsigned char set_bit(unsigned char c, int i){
	unsigned char  mask = 1 << i;
	return mask | c;
}

int is_bit_i_set(unsigned char comp,int i){

	unsigned char mask = 1 << i;
	return mask & comp;
}
int is_bit_i_set_short(unsigned short comp,int i){

	unsigned short mask = 1 << i;
	return mask & comp;
}
unsigned char deset_bit(unsigned char c,int i)
{
	int j;
	unsigned char mask = 1 << i;
    unsigned char retorno;
    for(j=0;j<7;j++)
    {
    	if(is_bit_i_set(c,j) && !is_bit_i_set(mask,j))
    	{
    		retorno = set_bit(retorno,j);
    	}
    }
    return retorno;
}


