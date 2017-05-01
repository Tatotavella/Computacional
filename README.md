# Percolacion

El archivo simple.c contiene el código para construir una red, llenarla, imprimirla y etiquetarla. 
Se compiló en simple.e con : "gcc -o3 -Wall -o simple.e simple.c -lm" y se corre: "./simple.e TAMAÑO PROBA"
generando una red cuadrada e imprimiendola antes y despues del etiquetado. Dentro de principal.c se encuentran
implementados los métodos llenar, hoshen, actualizar, etiqueta_falsa, corregir_etiqueta, percola e imprimir.

Para el resto del trabajo se utilizó la libreria percolar que contiene todas las funciones utilizadas como
llenar, hoshen, actualizar, etiqueta_falsa, corregir_etiqueta, percola, imprimir, contador_clases, 
contador_tamanos, promedio, dispersion, pcritica, curvafp, curvaPinf y fractDim. El object file para incluir
en la compilacion se genero con "gcc -o3 -Wall -o percolar.o -c percolar.c"

----------------------------------------------------------------------
Punto 1 
----------------------------------------------------------------------

Se utilizaron los programas pcritica.e y curvafp.e
Calculo de pcritica punto 1a "gcc -o3 -Wall percolar.o pcritica.c -o pcritica.e -lm". Solo es necesario el tamaño 
de input y los resultados se escriben en /Resultados/pcrit/results.txt. Se ejecuta para varios tamaños de red
con el script pcritScript.sh. Los resultados se visualizan con pcritica.py.
Para la probabilidad de percolar F(p) (punto 1b) se compiló con "gcc -o3 -Wall percolar.o curvafp.c -o curvafp.e -lm". 
Los resultados se escriben en /Resultados/curvafp/curva_TAMAÑO.txt. Se ejecuta para los distintos tamaños
con el script curvafpScript.sh. Los limites de la curva se pueden modificar para hacer zonas con mas detalle
y mas puntos adentro del archivo curvafp.c.
Los resultados se visualizan con curvafp.py

----------------------------------------------------------------------
Punto 2
----------------------------------------------------------------------

"gcc -o3 -Wall percolar.o curvapinf.c -o curvapinf.e -lm"
curvapinfScript.sh para las distintas corridas 
Resultados/pinf/curva_TAMAÑO.txt. Pantallazo general
Visualizacion curvapinf.py

----------------------------------------------------------------------
Punto 3 
----------------------------------------------------------------------

hay que ingresar la proba
"gcc -o3 -Wall percolar.o fractDim.c -o fractDim.e -lm"
Resultados/fractDim/res_t_TAMAÑO_p_PROBA.txt
Se corre con fractDimScript.sh que tiene tamaños y probabilidades de corrida para hacerlo en el punto critico
Visualizacion y valor con fractDim.py

----------------------------------------------------------------------
Punto 4, 5 y 1d 
----------------------------------------------------------------------

Se utilizó nsfrag.e con distintos scripts. Se cuenta la cantidad de ocurrencias de cada tamaño de cluster.
En Resultados se escriben como "t_TAMAÑO_p_PROBABILIDAD.txt" 
"gcc -o3 -Wall percolar.o nsfrag.c -o nsfrag.e -lm"
Para el 1d nsPcritScript.sh para obtener ns en la probabilidad critica
Para el 4 se corre con distintas probabilidades y un tamaño fijo. Siempre se usa el programa nsfrag que recibe
tamaño y proba. scalingScript.sh

----------------------------------------------------------------------
Punto 6 
----------------------------------------------------------------------

Es como nsfrag pero sin considerar el percolante
"gcc -o3 -Wall percolar.o nsNoperco.c -o nsNoperco.e -lm"
gammaScript.sh
Visualizacion gamma.py
Matching gammaMatch.py





