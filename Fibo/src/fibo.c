#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Calcula recursivamente el numero n en la secuencua de Fibonacci
 */
long fibonacci(int n) {
	/* Reglas generales de la sucesion de Fibonacci:
	 * El primer numero (indice 0) es 0
	 * El segundo numero (indice 1) es 1
	 * Cualquier otro numero de la secuencia (indice > 1) sera igual a la suma de los 2 numeros anteriores en la 
	 * sucesion
	 */ 
	if (n == 0) return 0; // Regla 1
	if (n == 1) return 1; // Regla 2

	return fibonacci(n-1) + fibonacci(n-2); // Regla 3
}

/**
 * Contexto de calculo utilizando hilos. Cada hilo se encarga de calcular partes parciales de la suma de fibonacci
 */
void *fibonacci_thread(void* arg) {
	unsigned long *sum = calloc(1, sizeof(unsigned long)); // Asignamos memoria para la suma parcial, usando malloc para no perder la referencia
	// de la memoria al salir
	srandom(time(NULL));
	for(int i = 0; i < 100000; i++) { // Solo calculamos 1000000 numeros para sumar.
		*sum += fibonacci(random() % 20);
	}
	printf("Final hilo %ld. Suma: %lu\n", pthread_self(), *sum);
	return (void*)sum; // Retornamos la suma como un puntero void
}

int main(int argc, char **argv) {
	/**
		Para activar los hilos, ejecutar con la opcion -t
	 */

	int t = 0, opt;

	while ((opt = getopt(argc, argv, "t")) != -1)
		if ('t' == opt) 
			t = 1;
		else { fprintf(stderr, "Uso: %s [-t]\n",
                    argv[0]);
            exit(EXIT_FAILURE);}

	// Suma del millon de numeros Fibonacci
	unsigned long suma = 0ul;
	// Semilla de Generador de Numeros Aleatorios
	srandom(time(NULL));

	if (!t) { /* Secuencial */
		printf("Empezando monohilo\n");
		for (int i = 0; i < 1000000; i++) {
			// Durante 1 millon de iteraciones, calculamos el numero Fibonacci de un numero aleatorio entre 0 y 19, y lo agregamos a la sumatoria
			suma += fibonacci(random() % 20);
		}

		printf("Finalizado monohilo. "); // Final de ejecucion, impresion en pantalla.
	} else { /* Threads */

		printf("Empezando multihilo\n");
		pthread_t threads[10]; // Coleccion de hilos a crear
		for (int i = 0; i < 10; i++ ){
			// Creamos 10 hilos, los cuales cada uno calculara 100000 veces la suma. 100000*10 = 1000000 iteraciones
			pthread_create(&threads[i], NULL, fibonacci_thread, NULL);
		}

		void* parciales[10]; // coleccion de las sumas parciales
		for (int i = 0; i < 10; i++) {
			// Esperamos que terminen cada uno de los threads. antes de seguir ejecutando.
			// Guardamos el resultado parcial en un elemtno de la coleccion
			pthread_join(threads[i], &parciales[i]);
		}

		// Sumamos todos los resultados parciales
		for (int i = 0; i < 10; i++) {
			suma += *(int*)(parciales[i]);
			free(parciales[i]); // Liberamos la memoria del calloc realizada en la funcion del thread
		}

		printf("Finalizado multihilo. ");
	}

	printf("Suma: %lu\n", suma);

}
