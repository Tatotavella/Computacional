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
	float prob;
	if (argc==3){
		sscanf(argv[1],"%d",&n);
		sscanf(argv[2],"%f",&prob);
	}
	m=n; //Cuestiones historicas
	if(n>0 && prob>=0 && prob<=1){
		red=malloc(sizeof(int)*m*n);
		printf("Filas: %d, Col: %d, Proba: %f \n",n, n, prob);
	}else{
		printf("ERROR: Tamaño debe ser mayor a 0 y probabilidad entre 0 y 1\n");
		exit(EXIT_FAILURE);
	}


	//Dimension fractal y Masa del cluster infinito
	int itera=27000;
	float *masaInf;
	float *disp;	
	masaInf=malloc(sizeof(float));
	disp=malloc(sizeof(float));
	
	fractDim(red,n,itera,prob,masaInf,disp);

	char str[100];
	strcpy(str, "Resultados/fractDim/res_t_");
	char tam[50];
	sprintf(tam,"%d",n);
	strcat(str, tam);
	strcat(str, "_p_");
	char pr[50];
	sprintf(pr,"%.5f",prob);
	strcat(str, pr);
	strcat(str, ".txt");




	FILE *fp = fopen(str,"a");
	fprintf(fp,"%d\t\t%f\t\t%f\n",n,masaInf[0],disp[0]);	
	
	fclose(fp);
	
	free(masaInf);
	free(disp);
	free(red);
		
	
	return 0;
	
}
