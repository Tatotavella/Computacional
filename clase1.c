#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void llenar(int *red, int m, int n, float proba);
void imprimir(int *red, int m, int n);
int   hoshen(int *red, int m, int n);
int   actualizar(int *red,int *clase,int s1,int frag);
void  etiqueta_falsa(int *red,int *clase,int s1,int s2);
void  corregir_etiqueta(int *red,int *clase,int m,int n);
void contador_clases(int *red,int *clase,int m,int n);
void contador_tamanos(int *contClase,int *tamanos,int m,int n);
int percola(int *red,int m,int n);

int main(int argc, char *argv[]){

	int m=10;
	int n=10;
	float proba=0.5;

	if (argc==4){
		sscanf(argv[1],"%d",&m);
		sscanf(argv[2],"%d",&n);
		sscanf(argv[3],"%f",&proba);
	}
	printf("Filas: %d, Col: %d, Proba: %.2f \n",m, n, proba);

	int *red;
	red=malloc(sizeof(int)*m*n);
	

	llenar(red,m,n,proba);
	imprimir(red,m,n);
	hoshen(red,m,n);
	//printf("---------------------------------------------------------\n");
	//imprimir(red,m,n);
	
	int result;
	result=percola(red,m,n);
	if(result>0){
		printf("La red percoló con el cluster: %d\n",result);
	}else{
		printf("La red no percoló\n");
	}
	
	
	free(red);

	return 0;
	
}
void llenar(int *red, int m, int n, float proba){

	/*
	Llena una red de m por n con unos 
	y ceros con probabilidad proba
	*/

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

	/* 
	Imprime red en pantalla
	*/

	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){			
			printf("%4d",red[i*n-(n-j+1)]);
		}
		printf("\n");	
	}
}
int hoshen(int *red, int m, int n){

	/*
	Esta funcion implementa en algoritmo de Hoshen-Kopelman.
	Recibe el puntero que apunta a la red y asigna etiquetas 
	a cada fragmento de red.
	*/

	int i,j,k,s,s1,s2,frag;
	int *clase;

	frag=0; //Numero de etiqueta actual

	clase=(int *)malloc(ceil(m*n/2)*sizeof(int)); //Tal vez puede ser mas chico que m*n. Ver siguiente comment

	for(k=0;k<ceil(m*n/2);k++){ //Lleno el vector clase desde el 0. Tomo el entero mayor a m*n/2 que es situacion tablero de ajedrez (peor cantidad de clusters).
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
	printf("---------------------------------------------------------\n");
	imprimir(red,m,n);
	printf("---------------------------------------------------------\n");
	corregir_etiqueta(red,clase,m,n);
	imprimir(red,m,n);
	
	/*//Imprimo el vector clase
	printf("Vector clase \n");
	for(k=0;k<ceil(m*n/2);k++){ 
		printf("%d, ",clase[k]);
	}*/

	//Contador de tamaño de clusters
	int *contClase;
	contClase=(int *)malloc(ceil(m*n/2)*sizeof(int)); 
	for(k=0;k<ceil(m*n/2);k++){ //Lo lleno de ceros
		*(contClase+k)=0;
	}
	contador_clases(red,contClase,m,n);
	//Lo imprimo al contador
	printf("Contador de clases \n");
	printf("Etiqueta|Tamaño\n");
	for(k=0;k<ceil(m*n/2);k++){ 
		if(contClase[k]>0){
			printf("%d\t%d\n",clase[k],contClase[k]);
		}
		
	}

	//Contador de tamaños
	int *tamanos;
	tamanos=(int *)malloc(m*n*sizeof(int)); 
	for(k=0;k<m*n;k++){ //Lo lleno de ceros
		*(tamanos+k)=0;
	}
	contador_tamanos(contClase,tamanos,m,n);
	//Lo imprimo
	printf("Informacion sobre los Tamaños\n");
	printf("Tamaño|Cantidad\n");
	for(k=0;k<m*n;k++){ 
		if(tamanos[k]>0){
			printf("%d\t%d\n",k,tamanos[k]);
		}
		
	}

	
	free(clase);
	free(contClase);
	free(tamanos);

	return 0;
}
int   actualizar(int *red,int *clase,int s1,int frag){

	/*
	Funcion para actualizar la red cuando no hay conflictos. 
	Toma la posición que se quiere actualizar y la etiqueta 
	que tiene el vecino s1.
	Casos de no conflicto:     |0|         |0|         |1|  
							 |0|1|       |1|1|       |0|1|    
	*/

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
	}else{
		clase[s1]=-s2; //Nueva etiqueta falsa en s1
		clase[s2]=s2;
		*(red)=s2;
	}
}
void  corregir_etiqueta(int *red,int *clase,int m,int n){

	/*
	Funcion para corregir todas las etiquetas en el
	paso final del algoritmo Hoshen-Kopelman.
	Se recorre toda la red y se busca en el vector
	clase la etiqueta correcta.
	*/

	int s,i,j;
	for(i=0;i<m*n;i=i+n){
		for(j=0;j<n;j++){
			if (*(red+i+j)>0){
				s=*(red+i+j); //Valor de la etiqueta
				while(clase[s]<0){//Busco la etiqueta correcta de s
					s=-clase[s];
				}
				*(red+i+j)=s;
				clase[s]=s; //Guardo la correcta final en el vector clase				
			}
		}
	}	

}
void contador_clases(int *red,int *contClase,int m,int n){
	/*
	Funcion para contar el tamaño de los clusters de cada
	etiqueta. La informacion queda guardada en el vector
	conClase.
	*/
	int s,i,j;
	for(i=0;i<m*n;i=i+n){
		for(j=0;j<n;j++){
			if (*(red+i+j)>0){
				s=*(red+i+j); //Valor de la etiqueta
				contClase[s]++; //Sumo 1 al contador del tamaño del cluster con etiqueta s				
			}
		}
	}

}
void contador_tamanos(int *contClase,int *tamanos,int m,int n){
	/*
	Funcion para contar tamaños que aparecen de clusters.
	La informacion queda guardada en el vector
	tamanos.
	*/
	int s,i,j;
	for(i=0;i<ceil(m*n/2);i++){
		if (*(contClase+i)>0){
			s=*(contClase+i); //Valor del tamaño
			tamanos[s]++; //Sumo 1 al contador de cantidad de tamaños				
			}
		}
}
int percola(int *red,int m,int n){
	/*Devuelve 1 si el sistema percola 
	y 0 si no.
	*/
	int i,j,rta;
	int etiqArriba[(int)ceil(n/2)];//Como mucho hay n/2 etiquetas en la primer fila
	j=0;
	for(i=0;i<n;i++){
		if(red[i]>0){	
			etiqArriba[j]=red[i];
			j++;
		}

	}
	//Chequeo si aparece alguna etiqArriba en la parte de abajo
	rta=0;	
	for(i=0;i<n;i++){
		if(red[(m-1)*n+i]>0){//Recorro ultima fila
			for(j=0;j<ceil(n/2);j++){//Comparo con etiqArriba
				if(etiqArriba[j]==red[(m-1)*n+i]){
					rta=etiqArriba[j];
					break;
				}
			}
		}

	}
	return rta;
	

}



















