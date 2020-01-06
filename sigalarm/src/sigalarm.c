#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/* Indices de lectura y escritura en el file descriptor del pipe */
#define IREAD  0
#define IWRITE 1


// File descriptor
int fd[2];

// Escribe un mensaje en el pipe
void mandarMensaje(int signal) {
	// Cuando recibamos una señal de alarma, escribimos "Mensaje" en el pipe
	write(fd[IWRITE], "Mensaje\n", 8);
}

int main(int argc, char **argv) {
	pid_t c1, c2; // Procesos hijos

	// Verificamos que podamos abrir pipe
	if (pipe(fd) == -1) {
		fprintf(stderr, "Error abriendo pipe\n");
		exit(EXIT_FAILURE);
	}

	// Creamos el primer hijo, este se encargara de escribir.
	c1 = fork();
	if (c1 == 0) {
		close(fd[IREAD]);
		signal(SIGALRM, mandarMensaje); // Adjuntamos handler de señal de alarma
		for (int i = 0; i < 10; i++) {
			alarm(2); // Cada 2 segundos lanzamos una señal de alarma
			pause();
		}
		// Liberamos el descriptor de escritura
		close(fd[IWRITE]);
		exit(EXIT_SUCCESS); // Este proceso termino
	} else {
		c2 = fork();  // Creamos otro hijo. Este se encargara de leer

		if (c2 == 0) {
			// buffer de lectura
			char lectura[8];
			close(fd[IWRITE]); // No necesitamos escribir, asi que cerramos el descriptor
			while(read(fd[IREAD], &lectura, 8) > 0) {
				//Mientras tengamos lectura del file descriptor, la leemos y mostramos en pantalla
				write(STDOUT_FILENO, &lectura, 8);
			}

			close(fd[IREAD]); // Cerramos el descriptor
			exit(EXIT_SUCCESS); // Hemos tenido exito
		}

		// Esperamos que todos los procesos finalicen antes de terminar la ejecucion del programa principal
		wait(NULL);
	}

	return 0;
}
