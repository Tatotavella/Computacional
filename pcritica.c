#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "percolar.h"

int main(int argc, char *argv[]){

	/* Valores default e inicializacion */
	int *red;
	int m=0;
	int n=0;
	if (argc==2){
		sscanf(argv[1],"%d",&n);
	}
	m=n; //Cuestiones historicas
	if(n>0){
		red=malloc(sizeof(int)*m*n);
		printf("Filas: %d, Col: %d\n", n, n);
	}else{
		printf("ERROR: Tamaño debe ser mayor a 0\n");
		exit(EXIT_FAILURE);
	}
	//Calculo de pcritica
	int itera=27000;
	int divisiones=16;

	float *critica; 
	float *disp;	
	critica=malloc(sizeof(float));
	disp=malloc(sizeof(float));
	
	pcritica(red,n,itera,divisiones,critica,disp);

	char str[100];
	strcpy(str, "Resultados/pcrit/results.txt");
	FILE *fp = fopen(str,"a");
	fprintf(fp,"%d\t\t%f\t\t%f\n",n,critica[0],disp[0]);	
	fclose(fp);

	
	free(red);
	free(critica);
	free(disp);	
	
	return 0;
	
}
