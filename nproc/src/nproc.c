#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
	struct rlimit rlim; // Estructura que almacena los limites de procesamiento
	getrlimit(RLIMIT_NPROC, &rlim); // Hacemos una llamada al sistema con la api de linux
	printf("Numero de procesos que puede tener el usuario en activo: %lu\n", rlim.rlim_max);
}
