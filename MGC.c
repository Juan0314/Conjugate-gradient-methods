/* Implementación del Método de Gradiente Conjugado Parcial
 * 
 *
 * Juan Antonio Vázquez Morales
 * 3 de noviembre de 2017
 *
 * Las siguientes lineas de código se crean con el propósito de implementar 
 * el Algoritmo de Gradiente Conjugado Parcial.
 */

/*-------------------------Librerías básicas de C-------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*---------Librerías creadas para la implementación del Algoritmo---------*/

/* La librería FuncionesMemoriaYArchivos.h contiene funciones para el 
 * manejo de la memoria dinámica y los archivos.
 */
#include "MemoriaYArchivos.h"

/* La librería FuncionesMatricesMGC.h contiene funciones para operaciones 
 * relacionadas con operaciones de matrices y asignación de variables de
 * acuerdo al Método de Gradiente Conjugado Parcial.
 */
#include "MatricesMGC.h"

/*---------------Comienza las lineas de código para el MGC---------------*/
int main(int argc, char **argv){
	/* Definición de variables */
	/* Variables enteras */
	int n,m,k,i;
	/* Matrices y vectores */
	double **A,*b,*x,*r,*p,*z;
	/* Variables reales */
	double ERROR,alpha,beta,gamma,rho;

	/* Se crea un apuntador para el archivo donde se almacena los datos
	 * del sistema
	 */ 
	FILE *Archivo;

	/* Se abre el archivo que contiene el sistema lineal */
	Archivo=fopen(argv[1],"r");

	/* Se verifica que el archivo este abierto */
	if(Archivo!=NULL){

		/* Se lee la dimensión del sistema */
		fscanf(Archivo,"%d",&n);

		/* Memoria para la matriz A de dimensión nxn */
		A=NuevaMatriz(n);

		/* Memoria para los vectores */
		x=NuevoVector(n);
		b=NuevoVector(n);
		r=NuevoVector(n);
		p=NuevoVector(n);
		z=NuevoVector(n);

		/* Se verifica que los vectores si se crearon */
		if(A!=NULL && b!=NULL && x!=NULL && 
		 r!=NULL && p!=NULL && z!=NULL){

			/* Se comienza por leer los datos */
			CargarSistema(Archivo,n,A,b,x);
			
			/* Se pide el número de iteraciones máximo */
			do{
				printf("Máximo de iteraciones 0<m<%d? ",n);
				scanf("%d",&m);
			}while(m<=0 || m>n-1);

			/* Se pide el ERROR */
			do{
				printf("ERROR>0? ");
				scanf("%lf",&ERROR);
			}while(ERROR<=0);

			/* Se inicia el Método de Gradiente Conjugado 
			 * Parcial 
			 */
			
			/* Datos iniciales */
			k=0;

			/* Cálculo de r0 */
			Calculo_r0(n,A,x,b,r);

			/* Cálculo de p0 */
			ProductoConstanteVector(n,-1.0,r,p);

			/* Cálculo de rho */
			rho=ProductoVectores(n,r,r);

			/* Comienzan las iteraciones */
			while(k<m+1 && sqrt(rho)>=ERROR){
				/* Cálculo de z */
				ProdMatrizVector(n,A,p,z);

				/* Cálculo de alphak */
				alpha=rho/ProductoVectores(n,p,z);

				/* Cálculo de xk */
				Calculo_dk(n,alpha,p,x);

				/* Cálculo de rk */
				Calculo_dk(n,alpha,z,r);

				/* Cálculo de gamma */
				gamma=rho;

				/* Cálculo de rho */
				rho=ProductoVectores(n,r,r);

				/* Cálculo de betak*/
				beta=rho/gamma;

				/* Cálculo de pk */
				Calculo_pk(n,beta,r,p);

				/* Se incrementa k */
				k=k+1;
			}

			/* Se imprime solución */
			printf("Iteraciones: %d\n",k);
			for(i=0;i<n;i++) printf("\ty%d = %g\n",i+1,x[i]);
			printf("Norma del último residuo: %g\n",sqrt(rho));
		}
		else printf("Memoria insuficiente");

		/* Se libera memoria */
		/* Se libera la matriz A si es necesario */
		if(A!=NULL) LiberarMatriz(A,n);
		/* Se libera los vectores si es necesario */
		if(x!=NULL) free(x);
		if(b!=NULL) free(b);
		if(r!=NULL) free(r);
		if(p!=NULL) free(p);
		if(z!=NULL) free(z);

		/* Se cierra el archivo */
		fclose(Archivo);
	}
	else printf("El archivo no fue abierto");
}


