#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){//gera o arquivo gigante de entrada
	long long int i,x;
	for(i=0;i<50000;i++){
		x = rand()%10000;
		printf("%lld\n",x);
	}
	return 0;
}
