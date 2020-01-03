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
		// Conforme vamos iterando, aumentamos el tamaño de memoria a alocar
		alloc_size += sizeof argumentos[i]; // Este tamaño de alocacion no contiene los espacios que separan los argumentos
	}

	// Alojamos espacio suficiente para cada espacio que vaya entre los argumentos
	return alloc_size + (num_argumentos - 1);
}

/**
 * A partir del numero de argumentos, parsea un vector de argumentos que fueron pasados a
 * este programa, y devuelve un string con un comando con sus respectivos argumentos, listo
 * para ser usado por system()s
 */
char *parse_args(int num_argumentos, char **argumentos) {
	int i;
	// Tamaño de memoria para el string a crear
	size_t alloc_size = get_alloc_size(num_argumentos, argumentos);
	// Creamos una nueva cadena
	char *args_str = malloc(alloc_size); 

	for (i = 1; i < num_argumentos; i++) {
		// Concatenamos cada argumento a la cadena
		strcat(args_str, argumentos[i]);
		if (i != (num_argumentos -1)) {
			// Separamos los argumentos por espacios, evitando colocarle al ultimo
			strcat(args_str, " ");
		}
	}

	return args_str;
}



int main(int argc, char **argv) {
	if (argc >= 2)  {
		struct timespec inicio_tp, final_tp;
		// Obtenemos un string con la ejecucion del programa a medir
		char *programa = parse_args(argc, argv);
		// Medimos el momento de reloj antes de iniciar la ejecucion
		clock_t inicio_cpu = clock();
		clock_gettime(CLOCK_REALTIME, &inicio_tp);

		system(programa); // Ejecutamos
		clock_gettime(CLOCK_REALTIME, &final_tp);
		// Medimos el tiempo posterior a la ejecucion del programa
		clock_t final_cpu = clock();
		time_t inicio = inicio_tp.tv_sec;
		time_t final = final_tp.tv_sec;

		printf("Tiempo CPU: %lims\nTiempo Real: %llds\n", final_cpu - inicio_cpu, (long long)(final - inicio));
	} else {
		printf("Uso: timeprog <prog> <arg1> <arg2> <arg3> ... <argn>\n");
		return 1;
	}

	return 0;

}

