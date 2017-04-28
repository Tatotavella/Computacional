import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def lineal(x, m, b):
	return m*x+b

#Pcritica. Calculo de pcritica para distintos tamanos de red. Cada punto tiene 27000 realizaciones y cada realizacion
#se obtiene con 16 divisiones sucesivas del valor de pcritica.

data_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados
rel_path = "Resultados/pcrit/results.txt"
direc = os.path.join(data_dir, rel_path)

redsize=[]
pcrit=[]
disp=[]

f = open(direc, 'r')
next(f) #Salteo header
for line in f:
	inter = [x for x in line.split('\t\t')]
	redsize.append(int(inter[0]))
	pcrit.append(float(inter[1]))
	disp.append(float(inter[2]))

xdata=disp[6:]
ydata=pcrit[6:]
popt, pcov = curve_fit(lineal, xdata, ydata)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(0,xdata[0],100)
yfit=popt[0]*xfit+popt[1]
print("Pc(inf): "+str(popt[1])+" err: "+str(perr[1]))
plt.plot(xfit,yfit)

plt.xlabel(r'$Dispersion \ \ \sigma$',size=20)
plt.ylabel(r'$p_{c}$',size=20)
plt.plot(disp,pcrit,'o')
plt.show()

plt.xlabel(r'$L$',size=20)
plt.ylabel(r'$p_{c}$',size=20)
plt.errorbar(redsize,pcrit,yerr=disp,fmt='*')
plt.show()
#'''

#Logaritmico
redsizeLog=[]
pcritLog=[]
errs=[]
pcinf=popt[1]
for i in range(len(redsize)):
	redsizeLog.append(np.log(redsize[i]))
	pcritLog.append(np.log(np.abs(pcinf-pcrit[i])))
	errs.append(disp[i]/np.abs(pcinf-pcrit[i]))	

#Muy sensible el valor de nu al rango de estos puntos que se eligen
xdata=redsizeLog[4:11]
ydata=pcritLog[4:11]
yerrs=errs[4:11]
popt, pcov = curve_fit(lineal, xdata, ydata,sigma=yerrs)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
yfit=popt[0]*xfit+popt[1]
print("Pendiente: "+str(popt[0])+" err: "+str(perr[0]))
print("Ordenada: "+str(popt[1])+" err: "+str(perr[1]))
plt.plot(xfit,yfit)

plt.errorbar(redsizeLog,pcritLog,yerr=errs,fmt='*')
plt.xlabel(r'$log(L)$',size=20)
plt.ylabel(r'$log(p_{c}(L)-p_c(\infty))$',size=20)
plt.show()

#'''
