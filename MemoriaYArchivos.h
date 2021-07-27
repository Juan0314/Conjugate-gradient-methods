/* Librería MemoriaYArchivos.h
 *
 * Juan Antonio Vázquez Morales.
 * 7 de septiembre de 2017.
 *
 * Funciones diversas para manipulación de archivos y reservar memoria de
 * matrices.
 *
 * Todas estas funciones fueron creadas para matrices cuadradas, es decir, la
 * matriz A es de tamaño nxn.
 */


/*-------------------Declaración de todas las funciones-------------------*/
/*Funciones para archivos*/
void CargarSistema(FILE *arch,int n,double **A,double b[],double x0[]);
void CargarA(FILE *arch,int n,double **A);
/*Funciones para memoria*/
double *NuevoVector(int n);
double **NuevaMatriz(int n);
void LiberarMatriz(double **a,int m);


/*-------------------Funciones ó Procesos para archivos-------------------*/

void CargarSistema(FILE *arch,int n,double **A,double b[],double x0[]){
	/* Proceso para leer los datos del sistema Ax = b, y el punto x0.
	 *
	 * Parámetros:
	 * arch, apuntador al archivo.
	 * n, número de variables.
	 * A, matriz A.
	 * b, vector b.
	 * x0, punto inicial.
	 */

	/* El formato del archivo debe contener de preferencia la 
	 * siguiente estructura:
	 * 1.- La primera linea es un entero, el valor de n seguido de un
	 *     salto de linea.
	 * 2.- Se tiene la matriz [A|b], cada elemento cada elemento de
	 *     cada fila es separado por un tabulador, y cada fila por un
	 *     salto de linea, incluso la última fila.
	 * 3.- El punto inicial x0 es de tal forma que cada elemento del 
	 *     vector esta separado por un salto de linea.
	 */

	/* Declaración de variables para el ciclo de lectura */
	int i,j;
	
	/* Se lee [A|b] */
	for(i=0;i<n;i++){
		/* Se lee la i-ésima fila de Matriz A */
		for(j=0;j<n;j++) fscanf(arch,"%lf",&A[i][j]);
		/* Se lee la i-ésima entrada del vector b */
		fscanf(arch,"%lf",&b[i]);
	}
	/* Lectura del punto inicial */
	for(i=0;i<n;i++) fscanf(arch,"%lf",&x0[i]);
}

void CargarA(FILE *arch,int n,double **A){
	/* Proceso para leer los datos del sistema Ax = b, y el punto x0.
	 *
	 * Parámetros:
	 * arch, apuntador al archivo.
	 * n, tamaño de la matriz.
	 * A, matriz cuadrada.
	 */

	/* El formato del archivo debe contener de preferencia la 
	 * siguiente estructura:
	 * 1.- La primera linea es un entero, el valor de n seguido de un
	 *     salto de linea.
	 * 2.- Se tiene la matriz A, cada elemento cada elemento de
	 *     cada fila es separado por un tabulador, y cada fila por un
	 *     salto de linea.
	 */

	/* Declaración de variables para el ciclo de lectura */
	int i,j;
	
	/* Se lee A */
	for(i=0;i<n;i++){
		/* Se lee la i-ésima fila de Matriz A */
		for(j=0;j<n;j++) fscanf(arch,"%lf",&A[i][j]);
	}
}

/*------------------ -Funciones y procesos para Memoria--- ----------------*/

double *NuevoVector(int n){
	/* Función para crear un vector de tamaño n.
	 * 
	 * Parámetros: 
	 * n, tamaño del vector.
	 */
	
	/* Se crea apuntador del vector */
	double *y;
	
	/* Se asigna la memoria para el vector */
	y=(double *)malloc(n*sizeof(double));

	/* Se regresa la dirección de la memoria */
	return y;
}


double **NuevaMatriz(int n){
	/* Función que crea una matriz cuadrada 
	 * 
	 * Parámetros: 
	 * n, tamaño de la matriz.
	 */

	/* Apuntador para la matriz */
	double **p;

	/* Declaración de variable para el ciclo */
	int i;

	/* Memoria que guarda la dirección de cada fila */
	p=(double **)malloc(n*sizeof(double *));

	/* Se verifica que el vector de direcciones fue creado */
	if(p!=NULL){
		/* Se procede a crear cada fila */
		for(i=0;i<n;i++){
			/* Memoria para cada fila */
			p[i]=(double *)malloc(n*sizeof(double));

			/* Se verifica que se crea la fila, sino 
			 * se rompe el ciclo.
			 */
			if(p[i]==NULL) break;
		}

		/* Se verifica que se creara todas las filas */
		if(i!=n){
			printf("No se creo matriz\n");
			/* Se librera la memoria si se rompe el ciclo */
			LiberarMatriz(p,i);
		}
	}

	/* Se devuelve la dirección de la matriz */
	return p;
}


void LiberarMatriz(double **a,int m){
	/* Proceso que libera la memoria de una matriz 
	 *
	 * Parámetros:
	 * a, apuntador de la memoria de la matriz.
	 * m, número de filas que necesitan ser liberadas.
	 */

	/* Declaración de variable para el ciclo */
	int i;

	/* Ciclo que libera las filas necesarias */
	for(i=0;i<m;i++) free(a[i]);

	/* Se libera el vector de direcciones de las filas */
	free(a);

	/* Se retorna un valor nulo */
	a=NULL;
}


