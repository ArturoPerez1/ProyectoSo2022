#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Devuelve la cantidad de tamaño a alojar para todos los elementos de un vector de strings,
 * sumado a la memoria que ocupara cada caracter de Space que se le concatenara
 */
size_t get_alloc_size(int num_argumentos, char **argumentos) {
	size_t alloc_size = 0;
	int i;
	for (i = 0; i < num_argumentos; i++) {
		alloc_size += sizeof argumentos[i]; // Este tamaño de alocacion no contiene los espacios que separan los argumentos
	}

	// Alojamos espacio suficiente para cada espacio que vaya entre los argumentos
	return alloc_size + (num_argumentos - 1);
}

/**
 * A partir del numero de argumentos, parsea un vector de argumentos que fueron pasados a
 * este programa, y devuelve un string con un comando con sus respectivos argumentos, listo
 * para ser usado por system()
 */
char *parse_args(int num_argumentos, char **argumentos) {
	int i;
	size_t alloc_size = get_alloc_size(num_argumentos, argumentos);
	char *args_str = malloc(alloc_size); 

	for (i = 1; i < num_argumentos; i++) {
		strcat(args_str, argumentos[i]);
		if (i != (num_argumentos -1)) {
			strcat(args_str, " ");
		}
	}

	return args_str;
}


int main(int argc, char **argv) {
	if (argc >= 2)  {
		// char *programa = argv[1];
		// printf("%lu\n", get_alloc_size(argc, argv));
		char *programa = parse_args(argc, argv);
		printf("%s\n", programa);
		clock_t inicio = clock();
		system(programa);
		clock_t final = clock();

		printf("Tiempo inicio: %lims\nTiempo final: %lims\nTiempo ejecucion: %lims\n", inicio, final, (final - inicio));
	} else {
		printf("Uso: timeprog <prog> <arg1> <arg2> <arg3> ... <argn>\n");
		return 1;
	}

	return 0;

}

