#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "percolar.h"

void llenar(int *red, int n, float prob){
	/*
	Llena una red de n por n con unos 
	y ceros con probabilidad proba
	*/
	int i;
	float r;	
	for(i=0;i<n*n;i++){
		r = (float)rand()/(float)RAND_MAX;
		if(r<prob){
			red[i] = 1;
		}else{
			red[i] = 0;	
		}
	}
}

int hoshen(int *red,int n){
	/*
	Esta funcion implementa en algoritmo de Hoshen-Kopelman.
	Recibe el puntero que apunta a la red y escribe etiquetas 
	a cada fragmento de red.
	*/

	int i,j,k,s1,s2,frag;
	int *clase;
	int m=n;

	frag=0; //Numero de etiqueta actual

	clase=(int *)malloc(m*n*sizeof(int)); //Tal vez puede ser mas chico que m*n. Ver siguiente comment

	for(k=0;k<m*n;k++){ //Lleno el vector clase desde el 0. Tomo el entero mayor a m*n/2 que es situacion tablero de ajedrez (peor cantidad de clusters).
		*(clase+k)=0;//------------------------------->Lo lleno con su lugar
	}

	// Hago el etiquetado para el primer elemento de la red

	s1=0; //Supongo vecino virtual a la izquierda etiquetado para que se etiquete si está ocupado el primer lugar.
	frag=1; //Empiezo las etiquetas en el numero 2. El valor 1 es por como esta definida actualizar y lo necesito en 1 para el primer paso.
	// Si lo arranco en 2 y el if que sigue no entra cuando encuentre otro en la red con vecino nulo le va a asignar frag+1 y no van a empezar en 2. Tal vez no sea tanto problema que no empiecen en 2.
	if (*red){// Quiere decir si lo que esta en el lugar 0 de red es 1 (es decir TRUE)
		frag=actualizar(red,clase,s1,frag); // No tiene entorno etiquetado entonces genera una nueva.
	}

	// Etiquetado para la primera fila de la red.

	for(i=1;i<n;i++) //Lugar en memoria hasta n-1
	{	
	  if (*(red+i)) //Si hay un 1 en el lugar i de la primer fila
		{
			s1=*(red+i-1); //Etiqueta del elemento de la izquierda
			frag=actualizar(red+i,clase,s1,frag);
		}
	}
	// Etiquetado para el resto de las filas 

	for(i=n;i<m*n;i=i+n){
		// Etiqueto el primer elemento de la fila
		if (*(red+i)){ //Notar que red+n es el primer elemento de la segunda fila
		   s1=*(red+i-n); // Vecino de arriba
		   frag=actualizar(red+i,clase,s1,frag);
		}
		// Ahora recorro esa fila
		for(j=1;j<n;j++){
			if (*(red+i+j)){
				s1=*(red+i+j-1); //Vecino de la izquierda
				s2=*(red+i+j-n); //Vecino de arriba
				if (s1*s2>0){ //Ninguno nulo entonces buscamos etiqueta mas chica
					etiqueta_falsa(red+i+j,clase,s1,s2);
				}
				else{ 
					if(s1!=0){frag=actualizar(red+i+j,clase,s1,frag);}
					else{frag=actualizar(red+i+j,clase,s2,frag);}
				}
			}
		}
	}
	corregir_etiqueta(red,clase,n);
	
	free(clase);

	return 0;
}

int   actualizar(int *red,int *clase,int s,int frag){

	/*
	Funcion para actualizar la red cuando no hay conflictos. 
	Toma la posición que se quiere actualizar y la etiqueta 
	que tiene el vecino s1.
	Casos de no conflicto:     |0|         |0|         |1|  
							 |0|1|       |1|1|       |0|1|    
	*/

	int s1=s;//Cuestiones historicas

	if(s1>0){
		while(clase[s1]<0){//Busco la etiqueta correcta de s1
			s1=-clase[s1];
		}
	    *(red)=s1;   //Realizo el etiquetado correcto buscando en clase
	    return frag; //No actualizo frag
	}else{// Si esta rodeado de ceros
		*(red)=frag+1; //Genero una nueva etiqueta frag+1
		return frag+1; 

	}
}

void  etiqueta_falsa(int *red,int *clase,int s1,int s2){
	/*
	Funcion para resolver la situacion de conflicto
	con dos etiquetas vecinas distintas de 0. Busca
	la etiqueta verdadera en el vector clase y le
	asigna la menor a la posicion de la red. Ademas
	actualiza el vector clase con la nueva etiqueta
	falsa.
	*/

	while(clase[s1]<0){//Busco la etiqueta correcta de s1
			s1=-clase[s1];
	}
	while(clase[s2]<0){//Busco la etiqueta correcta de s2
			s2=-clase[s2];
	}
	//Me quedo con la menor de las verdaderas
	if(s1<s2){
		clase[s2]=-s1; //Nueva etiqueta falsa en s2
		clase[s1]=s1; // ¿Innecesario?
		*(red)=s1;
	}else if(s1>s2){
		clase[s1]=-s2; //Nueva etiqueta falsa en s1
		clase[s2]=s2;
		*(red)=s2;
	}else
		{
		*(red)=s1;
		clase[s1]=s1; //Dejo las mismas etiquetas
		clase[s2]=s2;
		}
}

void  corregir_etiqueta(int *red,int *clase,int n){

	/*
	Funcion para corregir todas las etiquetas en el
	paso final del algoritmo Hoshen-Kopelman.
	Se recorre toda la red y se busca en el vector
	clase la etiqueta correcta.
	*/

	int s,i,j;
	int m=n;//Cuestiones historicas

	for(i=0;i<m*n;i=i+n){
		for(j=0;j<n;j++){
			if (*(red+i+j)>0){
				s=*(red+i+j); //Valor de la etiqueta
				while(clase[s]<0){//Busco la etiqueta correcta de s
					s=-clase[s];
				}
				*(red+i+j)=s;
				//clase[s]=s; //Guardo la correcta final en el vector clase				
			}
		}
	}	

}

int percola(int *red,int n){
	/*Devuelve la etiqueta del 
	cluster que percola. Devuelve 0
	si no percola
	*/
	int m=n;//Cuestiones historicas
	int i,j,rta;
	int etiqArriba[n];
	int etiqAbajo[n];
	rta=0;
	for(i=0;i<n;i++){
		*(etiqArriba+i)=0;
		*(etiqAbajo+i)=0;
	}
	j=0;
	for(i=0;i<n;i++){//Etiquetas arriba
		if(red[i]>0){	
			*(etiqArriba+j)=red[i];
			j++;
		}

	}
	j=0;
	for(i=0;i<n;i++){//Etiquetas abajo
		if(red[(m-1)*n+i]>0){
			*(etiqAbajo+j)=red[(m-1)*n+i];
			j++;
		}
	}
	for(i=0;i<n;i++){//Comparacion
		for(j=0;j<n;j++){
			if(etiqArriba[i]==etiqAbajo[j] && etiqArriba[i]!=0){
				rta=etiqArriba[i];
				break;
			}
		}
	}
	return rta;
}

void imprimir(int *red, int n){

	/* 
	Imprime red en pantalla con espaciado 4
	*/
	int m=n;//Cuestiones historicas
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){			
			printf("%4d",red[i*n-(n-j+1)]);
		}
		printf("\n");	
	}
}
float promedio(float *array,int arraysize){
	int i;
	float prom=0;
	for(i=0;i<arraysize;i++){
		prom=prom+array[i];	
	}
	prom=prom/arraysize;
	return prom;	
}
float dispersion(float *array,int arraysize){
	int i;
	float disp=0;
	float prom=promedio(array,arraysize);
	
	for(i=0;i<arraysize;i++){
		disp=disp+(array[i]-prom)*(array[i]-prom);	
	}
	disp=sqrt(disp/arraysize);
	return disp;
}
void contador_clases(int *red,int *contClase,int n){
	/*
	Funcion para contar el tamaño de los clusters de cada
	etiqueta. La informacion queda guardada en el vector
	conClase.
	*/
	int s,i,j;
	int m=n; //Cuestiones historicas
	for(i=0;i<m*n;i=i+n){
		for(j=0;j<n;j++){
			if (*(red+i+j)>0){
				s=*(red+i+j); //Valor de la etiqueta
				contClase[s]++; //Sumo 1 al contador del tamaño del cluster con etiqueta s				
			}
		}
	}

}
void contador_tamanos(int *contClase,int *tamanos,int n){
	/*
	Funcion para contar tamaños que aparecen de clusters.
	La informacion queda guardada en el vector
	tamanos.
	*/
	int s,i;
	int m=n; //Cuestiones historicas
	for(i=0;i<m*n;i++){
		if (*(contClase+i)>0){
			s=*(contClase+i); //Valor del tamaño
			tamanos[s]++; //Sumo 1 al contador de cantidad de tamaños				
			}
		}
}
void pcritica(int *red, int n,int itera,int divisiones,float *critica, float *disp){
	/*
	Funcion que realiza un barrido cercano de pcritica.
	Realiza "itera" ciclos donde se realizan divisiones
	consecutivas para estimar pcritica y devuelve su 
	valor.
	*/
	int i,j;
	int result;
	float pcrit;
	float denominador;
	float *valoresPcrit;
	valoresPcrit=malloc(sizeof(float)*itera);

	for(i=0;i<itera;i++){
		srand(time(NULL)+i);
		pcrit=0.5;
		denominador=2.0;
		for(j=0;j<divisiones;j++){
			denominador=2.0*denominador;
			llenar(red,n,pcrit);
			hoshen(red,n);
			result=percola(red,n);
			if(result>0){
				pcrit+=(-1.0/denominador);
			}else{
				pcrit+=(1.0/denominador);
			}	
		}
		valoresPcrit[i]=pcrit;
	}
	*(critica)=promedio(valoresPcrit,itera);
	*(disp)=dispersion(valoresPcrit,itera);
	free(valoresPcrit);
}
float curvafp(int *red, int n,int itera,int puntos,float proba){
	/*
	Funcion que realiza la curva de probabilidad de 	
	percolar en puntos equespaciados. Cada punto
	es el promedio sobre "itera" repeticiones.
	*/
	int j;
	float valor;
	int favorables;
	int result;
	favorables=0;

	for(j=0;j<itera;j++){
		llenar(red,n,proba);
		hoshen(red,n);
		result=percola(red,n);
		if(result>0){
			favorables++;
		}
	}
	valor=(float)favorables/itera;
	return valor;
}
float curvaPinf(int *red,int n,int itera,int puntos,float proba){
	/*
	Funcion que realiza la curva P inf que es  	
	la masa del cluster percolante sobre m*n en 
	puntos equiespaciados
	*/
	int m=n; //Cuestiones historicas
	int j,k;
	float valor;
	int *contClase;
	int result;
	int masa;
	float masaParcial=0;
	contClase=(int *)malloc(m*n*sizeof(int)); 
	
	for(k=0;k<m*n;k++){
		*(contClase+k)=0;
	}
	for(j=0;j<itera;j++){
		llenar(red,n,proba);
		hoshen(red,n);
		result=percola(red,n);
		if(result>0){
			contador_clases(red,contClase,n);
			masa=contClase[result];
			masaParcial=masaParcial+masa;
			for(k=0;k<m*n;k++){//Vacio las clases
				*(contClase+k)=0;
			}
		}
	}
	valor = masaParcial/(float)(m*n*itera);
	free(contClase);

	return valor;
}
void fractDim(int *red, int n,int itera, float prob,float *masaInf,float *disp){
	/*
	Funcion que devuelve la masa promedio del cluster 
	percolante sobre "itera" repeticiones
	*/
	int m=n; //Cuestiones historicas
	int i,j,k;
	float *masas;
	int result;
	int *contClase;
	int cantPercolaciones=0;

	masas=malloc(sizeof(float)*itera);
	contClase=(int *)malloc(m*n*sizeof(int)); 
	
	for(k=0;k<m*n;k++){
		*(contClase+k)=0;
	}

	for(i=0;i<itera;i++){
		srand(time(NULL)+i);
		llenar(red,n,prob);
		hoshen(red,n);
		result=percola(red,n);
		if(result>0){
			contador_clases(red,contClase,n);
			masas[cantPercolaciones]=contClase[result];
			cantPercolaciones++;	
		}
		for(k=0;k<m*n;k++){
			*(contClase+k)=0;
		}
	}
	//Promedio y disp
	float prom=0;
	for(j=0;j<cantPercolaciones;j++){
		prom=prom+masas[j];
	}
	prom=prom/cantPercolaciones;
	*(masaInf)=prom;
	float dispers=0;
	for(j=0;j<cantPercolaciones;j++){
		dispers=dispers+(masas[j]-prom)*(masas[j]-prom);
	}
	*(disp)=sqrt(dispers/cantPercolaciones);
	free(masas);
	free(contClase);
}
