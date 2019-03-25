#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){//gera o arquivo gigante de entrada com 1000 numeros
	long long int i,x;
	for(i=0;i<1000;i++){
		x = rand()%1000000;
		printf("%lld\n",x);
	}
	return 0;
}