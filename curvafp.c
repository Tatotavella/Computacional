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

	//Curva F(p)
	int itera=27000;
	int puntos=50;
	int i;
	float valor=0;
	float proba,ini,fin;
	ini = 0.0;
	fin = 1.0;

	char str[100];
	strcpy(str, "Resultados/curvafp/curva_");
	char cpi[50];
	sprintf(cpi,"%d",n);
	strcat(str, cpi);
	strcat(str, ".txt");
	FILE *fp = fopen(str,"w");
	fprintf(fp,"Probabilidad\t\tF(p)\n");

	for(i=0;i<puntos;i++){
		proba = ((fin-ini)*i)/(float)puntos + ini;
		srand(time(NULL)+i);
		valor = curvafp(red,n,itera,puntos,proba);
		fprintf(fp,"%f\t\t%f\n",proba,valor);
	}

	fclose(fp);
	free(red);
		
	
	return 0;
	
}
