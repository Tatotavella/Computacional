#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Programa que llena una red con cierta probabilidad con unos y ceros
// Argumentos de entrada: filas columnas proba

void llenarRed(int *red, int n_filas, int n_col, float proba);//Necesita saber dónde esta la red que va a modificar
void llenarRedRandom(int *red, int n_filas, int n_col, float proba);
float randomFloat(); // Genera un float aleatorio entre 0 y 1

int main(int argc, char *argv[]){
	//Tomo como argumentos de entrada: filas columnas proba
	int n_filas=atoi(argv[1]);// Con atoi convierto string to int
	int n_col=atoi(argv[2]);
	float proba=atof(argv[3]);// Con atof convierto string to float
	int *red; //Un lugar en memoria donde haya una red de enteros. Un array.
	red=malloc(sizeof(int)*n_filas*n_col);// En la direccion red tengo alocada memoria para que entre la red
	printf("Filas: %d, Col: %d, Proba: %.2f \n",n_filas, n_col, proba);

	//Lleno la red
	llenarRed(red,n_filas,n_col,proba);

    //Imprimo la red en pantalla. Se me complicó como interpretar el vector largo en matriz. No encontré manera mas limpia.
	int i,j;
	for(i=1;i<=n_filas;i++){
		for(j=1;j<=n_col;j++){			
			printf("%d",red[i*n_col-(n_col-j+1)]);
		}
		printf("\n");	
	}

	//Libero la alocacion dinamica
	free(red); 

	return 0;
	
}

float randomFloat(){ // Genera un float aleatorio entre 0 y 1
      float r = (float)rand()/(float)RAND_MAX;
      return r;
}

void llenarRed(int *red, int n_filas, int n_col, float proba){
	srand((unsigned int)time(NULL));   // should only be called once. Seed the randomizer.
	int i;
	float r;	
	for(i=0;i<n_filas*n_col;i++){
		r = randomFloat();
		if(r<proba){
			red[i] = 1;
		}else{
			red[i] = 0;	
		}
	}
}

void llenarRedRandom(int *red, int n_filas, int n_col, float proba){
	srand((unsigned int)time(NULL));   // should only be called once. Seed the randomizer.
//----------------INFO---------------------------------------------------------------------------------------------------------------------
//	int r = rand() % 10;      // rand() returns a pseudo-random integer between 0 and RAND_MAX. Modulus 10 gives random between 0 and 9 because it takes the remainder
//-------------------------------
//Macro: int RAND_MAX
//The value of this macro is an integer constant representing the largest value the rand function can return. In the GNU C Library, it is 2147483647, which is the largest signed integer representable in 32 bits. In other libraries, it may be as low as 32767.
//-----------------------------------------------------------------------------------------------------------------------------------------
	int i,r;	
	for(i=0;i<n_filas*n_col;i++){
		r = rand() % 2;
		red[i] = r;
	}	
}
