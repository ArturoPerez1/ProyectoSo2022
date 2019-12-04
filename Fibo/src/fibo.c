#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

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

int main(int argc, char **argv) {
	// Suma del millon de numeros Fibonacci
	unsigned long suma = 0l;
	// Semilla de Generador de Numeros Aleatorios
	srandom(time(NULL));
	for (int i = 0; i < 1000000; i++) {
		// Durante 1 millon de iteraciones, calculamos el numero Fibonacci de un numero aleatorio entre 0 y 19, y lo agregamos a la sumatoria
		suma += fibonacci(random() % 20);
	}

	printf("%lu\n", suma); // Final de ejecucion, impresion en pantalla.
}
