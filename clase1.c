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
float promedio(float *array,int arraysize);
float dispersion(float *array,int arraysize);
float pcritica(int *red,int m, int n,int itera,int divisiones);
void curvafp(int *red,int m, int n,int itera,int puntos);


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
/*
	llenar(red,m,n,proba);
	imprimir(red,m,n);
	hoshen(red,m,n);
	imprimir(red,m,n);
	int result;
	result=percola(red,m,n);
	if(result>0){
		printf("La red percoló con el cluster: %d\n",result);
	}else{
		printf("La red no percoló\n");
	}
*/
//---------------------------------------------------------------------
/*  
	//Calculo de pcritica
	int itera=27000;
	int divisiones=16;	
	pcritica(red,m,n,itera,divisiones);
//*/
//--------------------------------------------------------------------------
/*
	//Curva F(p)
	int itera=27000;
	int puntos=50;
	curvafp(red,m,n,itera,puntos);
//*/
//--------------------------------------------------------------------------	

	int i,k;
	float pcrit_16=0.587758;
	float pcrit_32=0.594091;
	float pcrit_64=0.592630;
	float pcrit_128=0.592557;
	int itera=27000;

	//Tamaño de los clusters

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
		if(i%1000==0){printf("%d\n",i);}
		llenar(red,m,n,pcrit_32);
		hoshen(red,m,n);

		contador_clases(red,contClase,m,n);      //Cuento tamaño de cada etiqueta
		contador_tamanos(contClase,tamanos,m,n); //Cuento ocurrencias de tamaños

		for(k=0;k<m*n;k++){
			*(contClase+k)=0;
		}


		
	}
	printf("Tamaños\n");
	for(k=0;k<m*n;k++){ 
		if(tamanos[k]>0){
			printf("%d,",k);
		}
	}
	printf("\n");
	printf("Cantidades\n");
	for(k=0;k<m*n;k++){ 
		if(tamanos[k]>0){
			printf("%d,",tamanos[k]);
		}
	}
	printf("\n");
	free(contClase);
	free(tamanos);
//*/

	free(red);
	

	return 0;
	
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
void llenar(int *red, int m, int n, float proba){

	/*
	Llena una red de m por n con unos 
	y ceros con probabilidad proba
	*/

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
	corregir_etiqueta(red,clase,m,n);
	
	free(clase);

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
				//clase[s]=s; //Guardo la correcta final en el vector clase				
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
	for(i=0;i<m*n;i++){
		if (*(contClase+i)>0){
			s=*(contClase+i); //Valor del tamaño
			tamanos[s]++; //Sumo 1 al contador de cantidad de tamaños				
			}
		}
}
int percola(int *red,int m,int n){
	/*Devuelve la etiqueta del 
	cluster que percola. Devuelve 0
	si no percola
	*/
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
float pcritica(int *red,int m, int n,int itera,int divisiones){
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
			llenar(red,m,n,pcrit);
			hoshen(red,m,n);
			result=percola(red,m,n);
			if(result>0){
				pcrit+=(-1.0/denominador);
			}else{
				pcrit+=(1.0/denominador);
			}	
		}
		valoresPcrit[i]=pcrit;
		if(i%1000==0){
			printf("pcrit: %f,paso:%d\n",pcrit,i);
		}
	}
	pcrit=promedio(valoresPcrit,itera);
	float disp;
	disp=dispersion(valoresPcrit,itera);
	printf("Valor de pcritica: %f, Dispersion: %f\n",pcrit,disp);
	free(valoresPcrit);


	return pcrit;
}
void curvafp(int *red,int m, int n,int itera,int puntos){
	/*
	Funcion que realiza la curva de probabilidad de 	
	percolar en puntos equespaciados. Cada punto
	es el promedio sobre "itera" repeticiones.
	*/
	int i,j;
	float probabilidad;
	int favorables;
	float *curva;
	int result;
	curva=malloc(sizeof(float)*puntos);
	
	for(i=0;i<puntos;i++){
		srand(time(NULL)+i);//Cada punto con una sola tira de numeros aleatorios?
		favorables=0;
		probabilidad=0.55+(i*0.1)/(float)puntos;
		for(j=0;j<itera;j++){
			llenar(red,m,n,probabilidad);
			hoshen(red,m,n);
			result=percola(red,m,n);
			if(result>0){
				favorables++;
			}
		}
		curva[i]=(float)favorables/itera;
		printf("%f,",curva[i]);
	}
	free(curva);
}



















