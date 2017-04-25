import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def lineal(x, m, b):
	return m*x+b

def beta(x,a,b,c):
	return a*(x**b)+c


#Pcritica. Calculo de pcritica para distintos tamanos de red. Cada punto tiene 27000 realizaciones y cada realizacion
#se obtiene con 16 divisiones sucesivas del valor de pcritica.
'''
redsize=[4,16,32,64,128]
pcrit=[0.562863,0.587758,0.594091,0.592630,0.592557]
disp=[0.103579,0.044650,0.027715,0.016976,0.009640]
plt.plot(disp,pcrit,'o')
plt.show()
#'''
'''
plt.xlabel('Largo de la red')
plt.ylabel('Probabilidad critica')
plt.errorbar(redsize,pcrit,yerr=disp,fmt='*')
plt.show()
#'''

#Con mas valores
redsize=[4,8,16,24,28,32,40,48,64,80,96,112,128,256]
pcrit=[0.562863,0.579404,0.587758,0.591330,0.591703,0.593926,0.592752,0.592809,0.592517,0.592630,0.592574,0.592486,0.592557,0.592741]
disp=[0.103579,0.070450,0.044650,0.034066,0.029225,0.027715,0.023418,0.020701,0.014367,0.016976,0.012398,0.010855,0.009640,0.005410]
xdata=disp[6:]
ydata=pcrit[6:]
popt, pcov = curve_fit(lineal, xdata, ydata)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(0,xdata[0],100)
yfit=popt[0]*xfit+popt[1]
print("pc(inf): "+str(popt[1])+" err: "+str(perr[1]))
plt.plot(xfit,yfit)

plt.xlabel('Dispersion')
plt.ylabel('Probabilidad critica')
plt.plot(disp,pcrit,'o')
plt.show()
plt.xlabel('Largo de la red')
plt.ylabel('Probabilidad critica')
plt.errorbar(redsize,pcrit,yerr=disp,fmt='*')
plt.show()


#Logaritmico
redsizeLog=[]
pcritLog=[]
errs=[]
for i in range(len(redsize)):
	redsizeLog.append(np.log(redsize[i]))
	pcritLog.append(np.log(np.abs(0.592506320354-pcrit[i])))
	errs.append(disp[i]/np.abs(0.592506320354-pcrit[i]))	

xdata=redsizeLog[3:]
ydata=pcritLog[3:]
yerrs=errs[3:]
popt, pcov = curve_fit(lineal, xdata, ydata,sigma=yerrs)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
yfit=popt[0]*xfit+popt[1]
print("Pendiente: "+str(popt[0])+" err: "+str(perr[0]))
print("Ordenada: "+str(popt[1])+" err: "+str(perr[1]))
plt.plot(xfit,yfit)

plt.errorbar(redsizeLog,pcritLog,yerr=errs,fmt='*')
#plt.plot(redsizeLog,pcritLog,'o')
plt.xlabel('log Largo red')
plt.ylabel('log pcrit(L)-pcrit(inf)')
plt.show()

#'''

#Funcion F(p). 50 puntos equiespaciados 27000 iteraciones por cada punto de la curva contando veces que percola.
#Codigo de los vectores: t_LARGORED

#Pantallazo general de la funcion
probas=[]
for i in range(50):
	probas.append(i/50.0)

t_8=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000148,0.000185,
0.000407,0.000926,0.002111,0.003333,0.006444,0.010148,0.017296,0.026111,0.042296,0.058815,0.085000,0.121556,0.161037,
0.209926,0.268704,0.331519,0.413407,0.484593,0.561185,0.639963,0.705407,0.777370,0.831148,0.877333,0.916296,0.944444,
0.968815,0.981370,0.988296,0.994815,0.997889,0.999111,0.999815,0.999963,0.999963,1.000000,1.000000,1.000000]

t_4=[0.000000,0.000000,0.000000,0.000000,0.000074,0.000481,0.001000,0.002222,0.004074,0.005963,0.009593,0.013704,0.019741,
0.028852,0.037815,0.051444,0.065296,0.083296,0.105630,0.129407,0.157111,0.187370,0.223185,0.255259,0.294000,0.337111,
0.386889,0.430222,0.485333,0.523630,0.569185,0.627704,0.668704,0.715185,0.753482,0.794481,0.832926,0.864667,0.891778,0.916333,
0.943519,0.958704,0.971000,0.982556,0.990111,0.995519,0.997593,0.999259,0.999889,1.000000]

t_16=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000037,0.000111,0.000037,0.000481,0.002815,0.005519,0.012037,0.023963,0.045815,0.082407,0.139037,0.215259,0.319370,
0.447630,0.558519,0.686963,0.792333,0.871296,0.928593,0.965074,0.982852,0.993630,0.997444,0.999185,0.999778,0.999926,1.000000,1.000000,
1.000000,1.000000,1.000000,1.000000,1.000000,1.000000]
t_32=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000037,0.000593,0.002519,0.011630,0.034370,0.090222,0.200889,0.372963,
0.563370,0.755963,0.885000,0.954000,0.986778,0.996704,0.999148,0.999778,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,
1.000000,1.000000,1.000000,1.000000,1.000000]
t_64=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000148,0.001185,0.013593,0.083630,0.292444,
0.627148,0.885889,0.979370,0.998148,0.999926,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,
1.000000,1.000000,1.000000,1.000000,1.000000]
t_128=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000222,0.010630,0.175148,
0.697519,0.975296,0.999593,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,
1.000000,1.000000,1.000000,1.000000,1.000000]
'''
plt.xlabel('Probabilidad de llenado')
plt.ylabel('Probabilidad de percolar')
plt.plot(probas,t_4,'*')
plt.plot(probas,t_8,'*')
plt.plot(probas,t_16,'*')
plt.plot(probas,t_32,'*')
plt.plot(probas,t_64,'*')
plt.plot(probas,t_128,'*')
plt.show()
#'''
#Detalle fino de la zona cercana al punto critico. En 0.6 +/- 0.05 . 50 puntos
probasFinas=[]
for i in range(50):
	probasFinas.append(0.55+i*0.1/50.0)

t_fino_4=[0.453000,0.456852,0.461370,0.468296,0.478704,0.472111,0.485148,0.486259,0.493370,0.497148,0.501667,0.508444,0.506815,0.510000,
0.517222,0.522704,0.534815,0.535556,0.537148,0.539741,0.545370,0.554333,0.556630,0.560778,0.568741,0.570000,0.580037,0.585259,0.589815,
0.585222,0.595556,0.606222,0.603000,0.614741,0.617593,0.621222,0.619963,0.634926,0.635296,0.643704,0.645296,0.650556,0.652593,0.655815,
0.661852,0.665889,0.672370,0.682593,0.676889,0.685148]
t_fino_8=[0.362741,0.380889,0.386407,0.394593,0.396000,0.410481,0.418222,0.420333,0.432148,0.439778,0.445852,0.455074,0.461926,0.468815,0.474074,
0.485593,0.488741,0.495815,0.505926,0.520407,0.522185,0.535370,0.534741,0.546074,0.555593,0.561741,0.568148,0.576963,0.589037,0.591741,
0.596407,0.606630,0.613593,0.621259,0.630963,0.641556,0.651037,0.647593,0.657741,0.668630,0.676889,0.681074,0.685407,0.698630,0.703630,
0.709222,0.718111,0.726074,0.728778,0.740185]
t_fino_16=[0.267519,0.281259,0.292704,0.299259,0.307556,0.321333,0.326185,0.337593,0.352815,0.361444,0.373407,0.385000,0.401000,0.415333,0.427407,
0.438111,0.450444,0.465037,0.476556,0.491000,0.508037,0.513407,0.529037,0.537778,0.553852,0.558407,0.578407,0.587296,0.598741,0.611000,
0.625519,0.639407,0.652111,0.661667,0.670037,0.681222,0.695630,0.706667,0.717667,0.725667,0.739519,0.750926,0.761778,0.770074,0.778741,
0.791667,0.802259,0.811037,0.819111,0.824593]
t_fino_32=[0.137444,0.148778,0.163370,0.173111,0.188074,0.201222,0.212074,0.228667,0.247037,0.258481,0.276259,0.297259,0.314778,0.333111,0.349926,
0.367926,0.385037,0.409296,0.428963,0.447148,0.463222,0.489519,0.511852,0.529926,0.547481,0.570296,0.592481,0.615630,0.633370,0.645222,
0.667556,0.684037,0.705556,0.722741,0.737704,0.755518,0.766778,0.785519,0.800667,0.813815,0.828741,0.838074,0.850074,0.863889,0.874741,
0.884963,0.893481,0.906778,0.913556,0.918519]
t_fino_64=[0.035704,0.045000,0.051667,0.060111,0.073778,0.080074,0.100000,0.109741,0.127370,0.147111,0.163444,0.189148,0.213037,0.237444,0.269852,
0.293593,0.326407,0.359519,0.392259,0.425667,0.459630,0.491370,0.529222,0.565037,0.591741,0.632630,0.662444,0.691852,0.724296,0.747296,
0.780296,0.803630,0.825852,0.845037,0.867259,0.885593,0.902000,0.912074,0.929037,0.937963,0.947074,0.959074,0.964259,0.969815,0.974259,
0.980407,0.984481,0.985000,0.989185,0.991185]
t_fino_128=[0.002074,0.002630,0.003815,0.006222,0.008111,0.010852,0.014296,0.021667,0.029630,0.038407,0.054407,0.068074,0.093037,0.114630,0.145556,
0.180296,0.218852,0.262741,0.312185,0.369333,0.423037,0.485333,0.537926,0.597815,0.650111,0.703481,0.758852,0.793148,0.833778,0.867111,
0.893148,0.918741,0.937593,0.952482,0.964778,0.975037,0.982407,0.986111,0.991037,0.993593,0.996111,0.997444,0.997667,0.998444,0.999222,
0.999333,0.999741,0.999778,0.999926,0.999963]
'''
plt.xlabel('Probabilidad de llenado')
plt.ylabel('Probabilidad de percolar')
plt.plot(probasFinas,t_fino_4,'*')
plt.plot(probasFinas,t_fino_8,'*')
plt.plot(probasFinas,t_fino_16,'*')
plt.plot(probasFinas,t_fino_32,'*')
plt.plot(probasFinas,t_fino_64,'*')
plt.plot(probasFinas,t_fino_128,'*')
plt.show()
'''
#Numero de fragmentos en funcion del tamano del cluster ns(s) en el punto critico. Uso la pcritica del barrido fino por divisiones.
#27000 redes analizadas

#pcrit_4=0.562863
#pcrit_16=0.587758
#pcrit_32=0.594091
#pcrit_64=0.592630
#pcrit_128=0.592557

data={}
datalog={}
script_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados

for i in [4,16,32,64,128]:

	key='tam_'+str(i)
	data[key]=[[],[]] #Una para tamanos y otra para ns

	rel_path = "Resultados/ns/tam_"+str(i)+".txt"
	direc = os.path.join(script_dir, rel_path)
	f = open(direc, 'r')
	next(f) #Salteo header
	for line in f:
		inter = [x for x in line.split('\t\t')]
		data[key][0].append(int(inter[0]))
		data[key][1].append(int(inter[1]))	

	datalog[key]=[[],[]]
	for i in range(len(data[key][0])):
		datalog[key][0].append(np.log(data[key][0][i]))
		datalog[key][1].append(np.log(data[key][1][i]))
	
	data[key][0]=np.asarray(data[key][0])
	data[key][1]=np.asarray(data[key][1])
	datalog[key][0]=np.asarray(datalog[key][0])
	datalog[key][1]=np.asarray(datalog[key][1])

f.close()
#boundsx=[1.2,3.7,5,6.1,6.8]
#boundsy=[8.3,6.3,4.8,3.9,3.6]
#tamas=[4,16,32,64,128]

tamas=[16,32,64,128]
boundsx=[3.7,5,6.1,6.8]
boundsy=[6.3,4.8,3.9,3.6]

for i in range(len(tamas)):
	key='tam_'+str(tamas[i])	
	#Fiteo lineal y plot
	xdata=datalog[key][0]
	xdata=xdata[xdata<boundsx[i]] #Solo la parte lineal	
	largo=len(xdata)
	xdata=xdata[8:]
	ydata=datalog[key][1]
	ydata=ydata[8:largo]	
	popt, pcov = curve_fit(lineal, xdata, ydata)
	perr = np.sqrt(np.diag(pcov))
	xfit=np.linspace(0,boundsx[i],100)
	yfit=popt[0]*xfit+popt[1]
	plt.plot(datalog[key][0],datalog[key][1],'o')
	plt.plot(xfit,yfit)
	print('Tam: '+str(tamas[i])+' Pend: '+str(popt[0])+' err: '+str(perr[0]))
	
	

plt.xlabel('Log Tamanos de cluster')
plt.ylabel('Log Ocurrencias')

plt.show()
#'''

#Curva P inf. 50 puntos equiespaciados 27000 iteraciones por cada punto de la curva contando la masa	
#del cluster percolante.
#Codigo de los vectores: t_LARGORED

#Pantallazo general de la funcion
probas=[]
for i in range(50):
	probas.append(i/50.0)

pInf_4=[0.000000,0.000000,0.000000,0.000046,0.000046,0.000178,0.000370,0.000590,0.001299,
0.002164,0.003350,0.005178,0.007729,0.011185,0.016125,0.020940,0.027051,0.036356,0.044280,
0.058690,0.074134,0.087949,0.107440,0.128079,0.151009,0.180639,0.207519,0.236424,0.273472,
0.309625,0.346900,0.389516,0.427058,0.468002,0.505743,0.548185,0.593813,0.632162,0.672951,
0.710266,0.745375,0.776979,0.812183,0.840676,0.866852,0.892972,0.915333,0.938674,0.959079,0.980030]

pInf_16=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000005,0.000028,0.000036,0.000252,0.000488,0.001146,
0.002947,0.006045,0.012312,0.024987,0.044463,0.076925,0.120088,0.181652,0.253856,0.335319,0.418185,
0.494616,0.565348,0.623375,0.670023,0.708279,0.740185,0.767438,0.791792,0.814647,0.836530,0.857992,
0.878766,0.899285,0.919654,0.939985,0.959961,0.979955]

pInf_32=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000004,
0.000020,0.000079,0.000655,0.002156,0.008392,0.023711,0.061862,0.131694,0.234757,0.354883,0.468692,
0.556464,0.620827,0.663482,0.697059,0.725104,0.750180,0.773553,0.795740,0.817337,0.838427,0.859066,
0.879480,0.899858,0.919872,0.939961,0.960021,0.979960]

pInf_64=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000015,0.000297,0.002558,0.019534,0.089062,0.241324,0.420052,0.542373,
0.607526,0.648342,0.679637,0.706433,0.730884,0.753872,0.775860,0.797353,0.818339,0.838940,0.859348,
0.879669,0.899834,0.919911,0.939957,0.960017,0.979992]

pInf_128=[0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
0.000000,0.000000,0.000000,0.000000,0.000000,0.000008,0.001819,0.043665,0.263301,0.490513,0.578285,
0.623137,0.656353,0.684218,0.709408,0.732873,0.755135,0.776746,0.797876,0.818664,0.839192,0.859522,
0.879737,0.899835,0.919949,0.939966,0.960004,0.979999]



'''
plt.xlabel('Probabilidad de llenado')
plt.ylabel('P infinito')
plt.plot(probas,pInf_4,'o')
plt.plot(probas,pInf_16,'o')
plt.plot(probas,pInf_32,'o')
plt.plot(probas,pInf_64,'o')
plt.plot(probas,pInf_128,'o')
plt.show()
#'''

#Detalle de curva Pinf. 50 puntos para poder ajustar y obtener beta
# Distintos detalles para cada tamano:
# 4   [0.1,0.5]
# 16  [0.36,0.7] 
# 32  [0.4, 0.7]
# 64  [0.45, 0.7]
# 128 [0.45, 0.7]
# 256 [0.5, 0.7]

dataPinf={}
dataPinfLog={}
script_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados
pcrits = [0.562863,0.587758,0.594091,0.592630,0.592557,0.592741]

n=0 #Grafico respecto de su Pcritica

for i in [4,16,32,64,128,256]:

	key='pInf_'+str(i)
	dataPinf[key]=[[],[]] #Una para tamanos y otra para ns
	dataPinfLog[key]=[[],[]]

	rel_path = "Resultados/pinf/tam_"+str(i)+".txt"
	direc = os.path.join(script_dir, rel_path)
	f = open(direc, 'r')
	next(f) #Salteo header
	for line in f:
		inter = [x for x in line.split('\t\t')]
		dataPinf[key][0].append(float(inter[0]) - pcrits[n])
		dataPinf[key][1].append(float(inter[1]))


		dataPinfLog[key][0].append(np.log(float(inter[0]) - pcrits[n]))
		dataPinfLog[key][1].append(np.log(float(inter[1])))	

	dataPinf[key][0]=np.asarray(dataPinf[key][0])
	dataPinf[key][1]=np.asarray(dataPinf[key][1])

	
	dataPinfLog[key][0]=np.asarray(dataPinfLog[key][0])
	dataPinfLog[key][1]=np.asarray(dataPinfLog[key][1])
	
	plt.figure(1)
	plt.subplot(211)
	plt.plot(dataPinf[key][0],dataPinf[key][1],'o')
	plt.subplot(212)
	plt.plot(dataPinfLog[key][0],dataPinfLog[key][1],'o')
	n+=1


f.close()

plt.figure(1)
plt.subplot(211)
plt.xlabel('Probabilidad de llenado - pc')
plt.ylabel('P infinito')
plt.subplot(212)
plt.xlabel('log Probabilidad de llenado - pc')
plt.ylabel('log P infinito')
plt.show()
#Detalle fino de Pinf para hacer el ajuste lineal de beta en el grafico logaritmico.

n=0
for i in [4,16,32,64,128,256]:
	key='pInf_'+str(i)
	xdata=[]
	ydata=[]
	for j in range(len(dataPinfLog[key][0])):
		if dataPinfLog[key][0][j]>-3.6:
			xdata.append(dataPinfLog[key][0][j])
			ydata.append(dataPinfLog[key][1][j])
	#plt.plot(xdata,ydata,'o')
	#plt.show()


	popt, pcov = curve_fit(lineal, xdata, ydata)
	perr = np.sqrt(np.diag(pcov))
	print("Tamano: "+str(i)+" Beta: "+str(popt[0])+" err: "+str(perr[0]))
	xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
	yfit=popt[0]*xfit+popt[1]
	plt.xlabel('log Probabilidad de llenado - pc')
	plt.ylabel('log P infinito')
	plt.plot(xdata,ydata,'o')
	plt.plot(xfit,yfit)
	n+=1


plt.show()
#'''



#Dimension fractal. Calculo de masa del cluster percolante en pcritica para distintos tamanos de red. Cada punto tiene 27000 realizaciones y cada realizacion
#se obtiene con la pcritica del punto a).
redsize=[4,16,32,64,128]
masasInf=[9.213852,109.244102,405.163635,1441.660034,5288.343262]
disp=[2.275835,26.826820,95.374405,344.041992,1259.488647]
#Grafico la densidad
densidadInf=[]
dispDensidad=[]
for i in range(len(masasInf)):
	densidadInf.append(masasInf[i]/(redsize[i]**2))
	dispDensidad.append(disp[i]/(redsize[i]**2))#Esta bien propagado el error?

logDens=[]
logSize=[]
logDisp=[]

for i in range(len(redsize)):
	logDens.append(np.log(densidadInf[i]))
	logSize.append(np.log(redsize[i]))	
	logDisp.append(dispDensidad[i]/densidadInf[i])
'''
plt.xlabel('Largo de la red')
plt.ylabel('Masa del cluster Inf en pc')
plt.errorbar(redsize,masasInf,yerr=disp,fmt='*')
plt.show()
#'''
'''
plt.xlabel('Largo de la red')
plt.ylabel('Densidad del cluster Inf en pc')
plt.errorbar(redsize,densidadInf,yerr=dispDensidad,fmt='*')
plt.show()
#'''

xdata=logSize
ydata=logDens
popt, pcov = curve_fit(lineal, xdata, ydata,sigma=logDisp)
perr = np.sqrt(np.diag(pcov))
xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
yfit=popt[0]*xfit+popt[1]
print("Dim fractal: "+str(popt[0]+2)+" err: "+str(perr[0])) # Ya que es D-d
plt.plot(xfit,yfit)


plt.xlabel('log Largo de la red')
plt.ylabel('log Densidad del cluster Inf en pc')
plt.errorbar(logSize,logDens,yerr=logDisp,fmt='*')
plt.show()
#'''

#Funcion f(z). Pantallazo general. Corridas para 20 puntos entre 0 y 1 de ns. La idea es graficar ns(p)/ns(pc) usando ns(pc) ya calculado
#en 1d)
probas=['0.05000','0.10000','0.15000','0.20000','0.25000','0.30000','0.35000','0.40000','0.45000','0.50000','0.55000',
		'0.60000','0.65000','0.70000','0.75000','0.80000','0.85000','0.90000','0.95000','1.00000']

script_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados

pcritica64=0.592630

pc64=[[],[]] #ns del pcritico que ya calcule
rel_path = "Resultados/ns/tam_64.txt"
direc = os.path.join(script_dir, rel_path)
f = open(direc, 'r')
next(f) #Salteo header
for line in f:
	inter = [x for x in line.split('\t\t')]
	pc64[0].append(float(inter[0]))
	pc64[1].append(float(inter[1]))
#plt.plot(pc64[0],pc64[1],'*')


datafzeta={}
for i in range(len(probas)):
	key=probas[i]
	datafzeta[key]=[[],[]] #Una para tamanos y otra para ns
	rel_path = "Resultados/efezeta/proba_"+probas[i]+".txt"
	direc = os.path.join(script_dir, rel_path)
	f = open(direc, 'r')
	next(f) #Salteo header
	for line in f:
		inter = [x for x in line.split('\t\t')]
		datafzeta[key][0].append(float(inter[0]))
		datafzeta[key][1].append(float(inter[1]))

#Fijo un s y veo su ns para los distintos p
fragMin=60
fragMax=65
nros=[]
prs=[]
for j in pc64[0]:
	if j<fragMax and j>fragMin:
		nros.append(j)

for nro in nros: 
	prs=[]
	sigma=36.0/91
	eseSigma=nro**sigma
	zeta=np.zeros(20)
	for i in range(len(probas)):
		pr=float(probas[i])
		zeta[i]=(eseSigma*(pr-pcritica64))/pcritica64

	nspc=0 #Lo busco
	for i in range(len(pc64[0])):
		if pc64[0][i]==nro:
			nspc=pc64[1][i]

	nsp=np.zeros(20)
	#Lleno el vector con los tamanos de los clusters para las diferentes probas
	for j in range(len(probas)):
		key=probas[j]
		prs.append(float(probas[j]))
		for i in range(len(datafzeta[key][0])):
			if datafzeta[key][0][i]==nro:
				nsp[j]=datafzeta[key][1][i]/nspc
	plt.plot(zeta,np.log(nsp),'o')
plt.xlabel('zeta')
plt.ylabel('log ns(p)/ns(pc)')
plt.show()
#Busqueda del pmax. Grafico ns(p) con s fijo y busco su maximo. Luego grafico pmax - pc en funcion de s. Todo en log
fragMin=10
fragMax=60
nros=[]

maximos=[]
for j in pc64[0]:
	if j<fragMax and j>fragMin:
		nros.append(j)

prs=[]
for i in range(len(probas)):
	prs.append(float(probas[i]))

for nro in nros: 
	
	nsp=np.zeros(20)
	#Lleno el vector con los tamanos de los clusters para las diferentes probas
	for j in range(len(probas)):
		key=probas[j]
		for i in range(len(datafzeta[key][0])):
			if datafzeta[key][0][i]==nro:
				nsp[j]=datafzeta[key][1][i]
	argmax=np.argmax(nsp)
	maximos.append(np.log(np.abs(prs[argmax]-pcritica64)))
		
nrosLog=[]
for n in nros:
	nrosLog.append(np.log(n))

xdata=nrosLog
ydata=maximos
popt, pcov=curve_fit(lineal,xdata,ydata)
xfit=np.linspace(xdata[0],xdata[len(xdata)-1],100)
yfit=popt[0]*xfit+popt[1]
perr = np.sqrt(np.diag(pcov))
print("Sigma: "+str(popt[0])+" err: "+str(perr[0]))
plt.plot(xfit,yfit)

plt.plot(nrosLog,maximos,'o')

plt.xlabel('log Tamano cluster')
plt.ylabel('log p max - pc (L)')
plt.show()
#'''


#Gamma matching. Pantallazo general. Corridas para 20 puntos entre 0.58 y 0.6 de ns con tamano de red de 128. La idea es graficar Suma de ns(p)s^2 siendo el segundo momento de la distribucion
#en 1d)
probas=['0.5800','0.5810','0.5820','0.5830','0.5840','0.5850','0.5860','0.5870','0.5880','0.5890','0.5900',
		'0.5910','0.5920','0.5930','0.5940','0.5950','0.5960','0.5970','0.5980','0.6000']

script_dir = os.path.dirname(__file__) #<-- Directorio absoluto donde estan los resultados

pcritica128=0.592557

m2=[]
prs=[]
for i in probas:
	rel_path = "Resultados/gammamatch/proba_"+i+".txt"
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
		elem2=elem2+ns*s*s

	m2.append(elem2)
	prs.append(float(i) - pcritica128)

plt.xlabel('Probabilidad de llenado - pc')
plt.ylabel('M2')
plt.plot(prs,m2,'o')
plt.show()






















