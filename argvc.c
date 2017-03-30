#include <stdio.h>
#include <stdlib.h>
//Llamar al programa con varios argumentos y muestra el funcionamiento de argv y argc
int main(int argc, char *argv[]){
	printf("Pointer argv: %p \n",argv);
	for(int i=0;i<argc;i++){
		printf("Argumento numero: %d, Valor: %s \n", i, argv[i]);
	}
	return 0;
}
