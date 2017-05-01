import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def lineal(x, m, b):
	return m*x+b

#Gamma matching. Pantallazo general. Corridas para 20 puntos entre 0.58 y 0.6 de ns con tamano de red de 128. La idea es graficar Suma de ns(p)s^2 siendo el segundo momento de la distribucion
#en 1d)
pcritica=[0.5871,0.592557]
n=0
for tam in [6,128]:

	data_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados
	rel_path = "Resultados/nsNoperco/listaProbas.txt"
	direc = os.path.join(data_dir, rel_path)
	f = open(direc, 'r')
	probas=[]
	for line in f:
		probas.append(line[:len(line)-1])


	script_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados

	itera=27000
	m2=[]
	prs=[]
	for i in probas:
		rel_path = "Resultados/nsNoperco/t_"+str(tam)+"_p_"+i+".txt"
		direc = os.path.join(script_dir, rel_path)
		f = open(direc, 'r')
		next(f) #Salteo header
		s=0
		ns=0	
		elem2=0
		for line in f:
			inter = [x for x in line.split('\t\t')]
			s=float(inter[0])
			ns=float(inter[1])
			elem2=elem2+(ns*s*s)/(tam*tam*itera)

		m2.append(elem2)
		prs.append(float(i) - pcritica[n])

	#G+ y G-
	maxiM2=np.max(m2)
	argummax=np.argmax(m2)
	prmax=prs[argummax]
	gammamenos=[]
	prmenos=[]
	gammamas=[]
	prmas=[]
	#Centro todo en prmax y tomo valor absoluto para hacer coincidir las curvas G+ y G-
	for i in range(len(m2)):
		if prs[i]<prmax:
			gammamenos.append(m2[i])
			prmenos.append(np.abs(prs[i]-prmax))
		else:
			gammamas.append(m2[i])
			prmas.append(np.abs(prs[i]-prmax))


	plt.xlabel('Probabilidad de llenado - pc')
	plt.ylabel('M2')
	plt.plot(prs,m2,'o')
	plt.show()
	plt.xlabel('mod Probabilidad de llenado - pc - prmax')
	plt.ylabel('M2')
	plt.plot(prmas,gammamas,'ro')
	plt.plot(prmenos,gammamenos,'bo')
	plt.show()

	gmasLog=[]
	prmasLog=[]
	gmenosLog=[]
	prmenosLog=[]
	for j in range(len(gammamas)):
		gmasLog.append(np.log(gammamas[j]))
		prmasLog.append(np.log(prmas[j]))
	for j in range(len(gammamenos)):
		gmenosLog.append(np.log(gammamenos[j]))
		prmenosLog.append(np.log(prmenos[j]))

	plt.plot(prmasLog,gmasLog,'o')
	plt.plot(prmenosLog,gmenosLog,'*')
	plt.xlabel('log Probabilidad de llenado - pc -prmax')
	plt.ylabel('log M2')
	plt.show()
	n=n+1





