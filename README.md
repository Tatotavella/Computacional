# Percolacion

El archivo simple.c contiene el código para construir una red, llenarla, imprimirla y etiquetarla. 
Se compiló en simple.e con : "gcc -o3 -Wall -o simple.e simple.c -lm" y se corre: "./simple.e TAMAÑO PROBA"
generando una red cuadrada e imprimiendola antes y despues del etiquetado. Dentro de principal.c se encuentran
implementados los métodos llenar, hoshen, actualizar, etiqueta_falsa, corregir_etiqueta, percola e imprimir.

Para el resto del trabajo se utilizó la libreria percolar que contiene todas las funciones utilizadas como
llenar, hoshen, actualizar, etiqueta_falsa, corregir_etiqueta, percola, imprimir, contador_clases, 
contador_tamanos, promedio, dispersion, pcritica, curvafp, curvaPinf y fractDim. El object file para incluir
en la compilacion se genero con "gcc -o3 -Wall -o percolar.o -c percolar.c". El número de iteraciones utilizado
a lo largo del trabajo fue de 27000.

----------------------------------------------------------------------
Punto 1 
----------------------------------------------------------------------

Se utilizaron los programas pcritica.e y curvafp.e
Para el cálculo de pcritica (punto 1a) se compiló con: "gcc -o3 -Wall percolar.o pcritica.c -o pcritica.e -lm".
Solo es necesario el tamaño de la red como input y los resultados se escriben en /Resultados/pcrit/results.txt. 
Se ejecuta para varios tamaños de red con el script pcritScript.sh. Los resultados se visualizan con pcritica.py.

Para la probabilidad de percolar F(p) (punto 1b) se compiló con: "gcc -o3 -Wall percolar.o curvafp.c -o curvafp.e -lm". 
Los resultados se escriben en /Resultados/curvafp/curva_TAMAÑO.txt. Se ejecuta para los distintos tamaños
con el script curvafpScript.sh. Los limites de la curva se pueden modificar para hacer zonas con mas detalle
y mas puntos adentro del archivo curvafp.c.
Los resultados se visualizan con curvafp.py

----------------------------------------------------------------------
Punto 2
----------------------------------------------------------------------

Para realizar la curva de la fuerza del cluster percolante (punto 2) se compiló con: 
"gcc -o3 -Wall percolar.o curvapinf.c -o curvapinf.e -lm". Los distintos tamaños se corrieron con el script curvapinfScript.sh.
Los resultados se escriben en Resultados/pinf/curva_TAMAÑO.txt. El script realiza un pantallazo general que se visualiza con 
curvapinf.py.

----------------------------------------------------------------------
Punto 3 
----------------------------------------------------------------------

Para obtener la dimensión fractal se compiló con: "gcc -o3 -Wall percolar.o fractDim.c -o fractDim.e -lm".
El programa requiere que se ingrese la probabilidad como input. Los resultados se escriben en 
Resultados/fractDim/res_t_TAMAÑO_p_PROBA.txt con esa notación.
Se corre con fractDimScript.sh que tiene tamaños y probabilidades de corrida para hacerlo en el punto critico.
Visualizacion y valor de la dimensión fractal con fractDim.py

----------------------------------------------------------------------
Punto 4, 5 y 1d 
----------------------------------------------------------------------

Para estos puntos se utilizó el programa nsfrag.e con distintos scripts. Éste cuenta la cantidad de ocurrencias de cada tamaño de cluster.
Los resultados se escriben en Resultados/ns como "t_TAMAÑO_p_PROBABILIDAD.txt". Se compiló con: "gcc -o3 -Wall percolar.o nsfrag.c -o nsfrag.e -lm". El programa recibe como input tamaño y probabilidad.
Para el punto 1d se usó nsPcritScript.sh para obtener ns en la probabilidad critica.
Para el 4 y 5 se corre con distintas probabilidades y un tamaño fijo en scalingScript.sh.

----------------------------------------------------------------------
Punto 6 
----------------------------------------------------------------------

Para este punto se utilizó un programa similar a nsfrag.e pero sin considerar el aporte del cluster percolante.
El programa se llama nsNoperco y se compiló con: "gcc -o3 -Wall percolar.o nsNoperco.c -o nsNoperco.e -lm".
Una corrida general se hace con gammaScript.sh y se visualiza con gamma.py. Se puede realizar la obtención
de gamma con gammaMatch.py.





