#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void llenar(int *red, int m, int n, float proba);
void imprimir(int *red, int m, int n);

int main(){
	int m=15;
	int n=15;
	float proba=0.6;
	int *red;
	red=malloc(sizeof(int)*m*n);
	printf("Filas: %d, Col: %d, Proba: %.2f \n",m, n, proba);

	llenar(red,m,n,proba);
	imprimir(red,m,n);
	
	free(red); 

	return 0;
	
}
void llenar(int *red, int m, int n, float proba){
	srand((unsigned int)time(NULL));
	int i;
	float r;	
	for(i=0;i<m*n;i++){
		r = (float)rand()/(float)RAND_MAX;
		if(r<proba){
			red[i] = 1;
		}else{
			red[i] = 0;	
		}
	}
}
void imprimir(int *red, int m, int n){
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){			
			printf("%d",red[i*n-(n-j+1)]);
		}
		printf("\n");	
	}
}
