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


	//Distribucion de tamaño de los clusters en prob sin contar el percolante
	int i,k;
	int itera=27000;
	int result;
	int *contClase;
	int *tamanos;
	contClase=(int *)malloc(m*n*sizeof(int)); 
	tamanos=(int *)malloc(m*n*sizeof(int)); 
	
	for(k=0;k<m*n;k++){
		*(contClase+k)=0;
		*(tamanos+k)=0;
	}

	srand((unsigned int)time(NULL));
    for(i=0;i<itera;i++){
		llenar(red,n,prob);
		hoshen(red,n);
		contador_clases(red,contClase,n);      //Cuento tamaño de cada etiqueta
		result=percola(red,n); //Veo el cluster percolante y lo saco del recuento
		if(result>0){
			contClase[result]=0; //Saco el percolante del recuento
		}
		contador_tamanos(contClase,tamanos,n); //Cuento ocurrencias de tamaños
		for(k=0;k<m*n;k++){
			*(contClase+k)=0; //Vacio este vector y acumulo todo en tamanos
		}	
	}
	char str[100];
	strcpy(str, "Resultados/nsNoperco/t_");
	char tam[50];
	sprintf(tam,"%d",n);
	strcat(str, tam);
	strcat(str, "_p_");
	char pr[50];
	sprintf(pr,"%.5f",prob);
	strcat(str, pr);
	strcat(str, ".txt");

	//Escribo en archivo dos columnas |Tamaños|Cantidades|
	FILE *fp = fopen(str,"w");
	fprintf(fp,"Tamaños\t\tCantidades\n");
	for(k=0;k<m*n;k++){ 
		if(tamanos[k]>0){
			fprintf(fp,"%d\t\t%d\n",k,tamanos[k]);
		}
	}	
	fclose(fp);

	//Lista de probas
	char strLista[100];
	strcpy(strLista, "Resultados/nsNoperco/listaProbas.txt");
	FILE *flista = fopen(strLista,"a");
	fprintf(fp,"%.5f\n",prob);
	fclose(flista);
	
	free(contClase);
	free(tamanos);

	free(red);
		
	
	return 0;
	
}
