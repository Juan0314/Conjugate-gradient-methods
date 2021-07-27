/* Librería MatricesMGC.h
 *
 * Juan Antonio Vázquez Morales
 * 3 de noviembre de 2017
 * 
 *
 * Funciones diversas de las operaciones con matrices necesarias en el Método
 * de Gradiente Conjugado.
 *
 * Las funciones y/o procesos que involucran una matriz requieren que esta 
 * sea cuadrada.
 */


/*-------------------Declaración de todas las funciones-------------------*/
void ProdMatrizVector(int n,double **Q,double x[],double res[]);
double ProductoVectores(int n,double x[],double y[]);
void SumaVectores(int n,double x[],double y[],double res[]);
void RestaVectores(int n,double x[],double y[],double res[]);
void ProductoConstanteVector(int n,double c,double x[],double res[]);
void Calculo_r0(int n,double **A,double x[],double b[],double r[]);
void Calculo_dk(int n,double c,double v[],double d[]);
void Calculo_pk(int n,double beta,double r[],double p[]);


/*-----------------------Funciones y procedimientos-----------------------*/

void ProdMatrizVector(int n,double **Q,double x[],double res[]){
	/* Proceso que obtiene el el resultado de multiplicar Qx
	 *
	 * Parámetros:
	 * n, tamaño de la matriz y vectores.
	 * Q, dirección de la matriz Q.
	 * x, dirección de la matriz x.
	 * res, dirección del vector resultante.
	 */

	/* Declaración de variables para el ciclo */
	int i,j;

	/* Ciclo que obtiene la multiplicación Qx */
	for(i=0;i<n;i++){
		res[i]=0.0;
		for(j=0;j<n;j++) res[i]+=(Q[i][j]*x[j]);
	}
}


double ProductoVectores(int n,double x[],double y[]){
	/* Función que obtiene <x,y>
	 *
	 * Parámetros:
	 * n, tamaño de los vectores.
	 * x, dirección del vector x.
	 * x, dirección del vector y.
	 */

	/* Declaración de la variable donde se guarda el resultado */
	double res=0.0;

	/* Declaración de variable para el ciclo */
	int i;
	
	/* Ciclo que obtiene <x,y> */
	for(i=0;i<n;i++) res+=(x[i]*y[i]);

	/* Se retorna el resultado */
	return res;
}


void SumaVectores(int n,double x[],double y[],double res[]){
	/* Proceso que suma dos vectores.
	 *
	 * Parámetros:
	 * n, tamaño de la vectores.
	 * x, dirección del vector x.
	 * y, dirección del vector y.
	 * res, dirección del vector resultante.
	 */

	/* Declaración de variable para el ciclo */
	int i=0;

	/* Ciclo que obtiene la suma */
	for(i=0;i<n;i++) res[i]=x[i]+y[i];

	/* Nota: En esta función si x se actualiza mediante está operación,
	 * res puede tener la dirección de x, lo cual no afecta el
	 * resultado.
	 */
}


void RestaVectores(int n,double x[],double y[],double res[]){
	/* Proceso que obtiene x-y.
	 *
	 * Parámetros:
	 * n, tamaño de la vectores.
	 * x, dirección del vector x.
	 * y, dirección del vector y.
	 * res, dirección del vector resultante.
	 */

	/* Declaración de variable para el ciclo */
	int i=0;

	/* Ciclo que obtiene la diferencia */
	for(i=0;i<n;i++) res[i]=x[i]-y[i];

	/* Nota: En esta función si x se actualiza mediante está operación, 
	 * res puede tener la dirección de x, lo cual no afecta el 
	 * resultado.
	 */
}


void ProductoConstanteVector(int n,double c,double x[],double res[]){
	/* Proceso que obtiene el producto de un vector por un escala
	 *
	 * Parámetros:
	 * n, tamaño del vector.
	 * c, constante real por la que se multiplica el vector.
	 * x, dirección del vector x.
	 * res, dirección del vector resultante.
	 */

	/* Declaración de variable para el ciclo */
	int i;

	/* Ciclo que obtiene c*y */
	for(i=0;i<n;i++) res[i]=c*x[i];

	/* Nota: En esta función si x se actualiza mediante está operación,
	 * res puede tener la dirección de x, lo cual no afecta el 
	 * resultado.
	 */
}


void Calculo_r0(int n, double **A, double x[],double b[],double r[]){
	/* Proceso que calcula el residuo inicial r0=Ax-b.
	 *
	 * Parámetros:
	 * n, tamaño de la vectores.
	 * A, dirección de la matriz.
	 * x, dirección del vector x.
	 * b, dirección del vector b.
	 * res, dirección del vector resultante.
	 */

	/* Se calcula Ax */ 
	ProdMatrizVector(n,A,x,r);

	/* Se procede a calcular Ax-b */
	RestaVectores(n,r,b,r);
}


void Calculo_dk(int n,double c,double v[],double d[]){
	/* Proceso que actualiza vectores de la forma d=d+cv
	 *
	 * Parámetros:
	 * n, tamaño de la vectores.
	 * c, longitud de paso.
	 * v, dirección del vector v.
	 * d, dirección del vector d.
	 */

	/* Declaración de variable para el ciclo */
	int i;

	/* Ciclo que obtiene d */
	for(i=0;i<n;i++) d[i]=d[i]+c*v[i];
}

/*Calculo de pk*/
void Calculo_pk(int n,double beta,double r[],double p[]){
	/* Proceso que actualiza vectores de la forma d=d+cv
	 *
	 * Parámetros:
	 * n, tamaño de la vectores.
	 * beta, constante del MGC.
	 * r, dirección del vector r.
	 * p, dirección del vector p.
	 */

	/* Declaración de variable para el ciclo */
	int i;

	/* Ciclo que obtiene pk del MGC */
	for(i=0;i<n;i++) p[i]=beta*p[i]-r[i];

	/* Nota: Este proceso actualiza p */
}


