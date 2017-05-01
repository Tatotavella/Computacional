import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

#Curva P inf. 50 puntos equiespaciados 27000 iteraciones por cada punto de la curva contando la masa	
#del cluster percolante.

#Pantallazo general de la funcion

data_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados


tams=[4,16,32,64,128,256]
for l in tams:
	proba=[]
	pinf=[]
	rel_path = "Resultados/pinf/curva_"
	rel_path+=str(l)
	direc = os.path.join(data_dir, rel_path)
	direc+=".txt"
	f = open(direc, 'r')
	next(f) #Salteo header
	for line in f:
		inter = [x for x in line.split('\t\t')]
		proba.append(float(inter[0]))
		pinf.append(float(inter[1]))
	plt.plot(proba,pinf,'o',label=l)

plt.legend(loc='upper left', numpoints=1)
plt.xlabel(r'$p$',size=20)
plt.ylabel(r'$P_{\infty}$',size=20)
plt.show()
