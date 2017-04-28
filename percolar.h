#ifndef _PERCOLAR_H_

#define _PERCOLAR_H_

	void  llenar(int *red,int n,float prob);
	int   hoshen(int *red,int n);
	int   actualizar(int *red,int *clase,int s,int frag);
	void  etiqueta_falsa(int *red,int *clase,int s1,int s2);
	void  corregir_etiqueta(int *red,int *clase,int n);
	int   percola(int *red,int n);
	void imprimir(int *red, int n);

	void contador_clases(int *red,int *clase,int n);
	void contador_tamanos(int *contClase,int *tamanos,int n);
	float promedio(float *array,int arraysize);
	float dispersion(float *array,int arraysize);
	void pcritica(int *red, int n,int itera,int divisiones,float *critica, float *disp);
	float curvafp(int *red, int n,int itera,int puntos,float proba);
	float curvaPinf(int *red,int n,int itera,int puntos,float proba);
	void fractDim(int *red, int n,int itera,float prob,float *masaInf,float *disp);

#endif
