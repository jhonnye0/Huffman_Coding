
int is_bit_i_set(unsigned char comp,int i);
int is_bit_i_set_short(unsigned short comp,int i);

unsigned char set_bit(unsigned char c, int i);


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