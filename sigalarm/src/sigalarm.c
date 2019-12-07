#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/* Indices de lectura y escritura en el file descriptor del pipe */
#define IREAD  0
#define IWRITE 1



int fd[2];

void mandarMensaje(int signal) {
	write(fd[IWRITE], "Mensaje\n", 8);
}

int main(int argc, char **argv) {
	pid_t c1, c2;

	if (pipe(fd) == -1) {
		fprintf(stderr, "Error abriendo pipe\n");
		exit(EXIT_FAILURE);
	}

	c1 = fork();
	if (c1 == 0) {
		close(fd[IREAD]);
		signal(SIGALRM, mandarMensaje);
		for (int i = 0; i < 10; i++) {
			alarm(2);
			pause();
		}
		close(fd[IWRITE]);
		exit(EXIT_SUCCESS);
	} else {
		c2 = fork();

		if (c2 == 0) {
			char lectura[8];
			close(fd[IWRITE]);
			while(read(fd[IREAD], &lectura, 8) > 0) {
				write(STDOUT_FILENO, &lectura, 8);
			}

			close(fd[IREAD]);
			exit(EXIT_SUCCESS);
		}

		wait(NULL);
	}

	return 0;
}
