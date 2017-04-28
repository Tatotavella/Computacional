import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

#Funcion F(p). 50 puntos equiespaciados 27000 iteraciones por cada punto de la curva contando veces que percola.
#Codigo de los vectores: curva_LARGORED

#Pantallazo general de la funcion

data_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados


tams=[4,16,32,64,128,256]
for l in tams:
	proba=[]
	fp=[]
	rel_path = "Resultados/curvafp/curva_"
	rel_path+=str(l)
	direc = os.path.join(data_dir, rel_path)
	direc+=".txt"
	f = open(direc, 'r')
	next(f) #Salteo header
	for line in f:
		inter = [x for x in line.split('\t\t')]
		proba.append(float(inter[0]))
		fp.append(float(inter[1]))
	plt.plot(proba,fp,'o',label=l)

plt.legend(loc='upper left', numpoints=1)
plt.xlabel(r'$p$',size=20)
plt.ylabel(r'$F(p)$',size=20)
plt.show()
