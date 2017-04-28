import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def lineal(x, m, b):
	return m*x+b

#Dimension fractal. Calculo de masa del cluster percolante en pcritica para distintos tamanos de red. Cada punto tiene 27000 realizaciones y cada realizacion
#se obtiene con la pcritica del punto a).

data_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados


redsize=[4,16,32,64,128,256]
probas=[0.561110,0.58813,0.59373,0.59222,0.59259,0.59275]
masasInf=[]
disp=[]
for i in range(len(redsize)):
	rel_path = "Resultados/fractDim/res_t_"
	rel_path+=str(redsize[i])
	rel_path+="_p_"
	rel_path+=str(probas[i])
	direc = os.path.join(data_dir, rel_path)
	direc+=".txt"
	f = open(direc, 'r')
	for line in f:
		inter = [x for x in line.split('\t\t')]
		masasInf.append(float(inter[1]))
		disp.append(float(inter[2]))
#Densidad y log
densidadInf=[]
dispDensidad=[]
for i in range(len(masasInf)):
	densidadInf.append(masasInf[i]/(redsize[i]**2))
	dispDensidad.append(disp[i]/(redsize[i]**2))

logDens=[]
logSize=[]
logDisp=[]

for i in range(len(redsize)):
	logDens.append(np.log(densidadInf[i]))
	logSize.append(np.log(redsize[i]))	
	logDisp.append(dispDensidad[i]/densidadInf[i])

xdata=logSize
ydata=logDens
popt, pcov = curve_fit(lineal, xdata, ydata,sigma=logDisp)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
yfit=popt[0]*xfit+popt[1]
print("Dim fractal: "+str(popt[0]+2)+" err: "+str(perr[0])) # Ya que es D-d
plt.plot(xfit,yfit)
plt.errorbar(logSize,logDens,yerr=logDisp,fmt='*')
plt.xlabel(r'$log(L)$',size=20)
plt.ylabel(r'$log \ \rho(p_{c})$',size=20)

plt.show()
#'''
