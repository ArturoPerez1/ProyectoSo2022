#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Determina si una ruta corresponde a un archivo regular
 */
int is_reg_file(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

/**
 * Copia cierta cantidad de bytes, determinados por buffsize, de src, hacia dest
 */
int copyfile(FILE *src, FILE *dest, size_t buffsize) {
	// Los contenidos pueden ser cualquier cosa. Alojamos memoria pero la guardamos en un puntero void.
	void *contents = malloc(buffsize);
	// Guardamos los contenidos en el puntero void. Esto podria ser binario o textual.
	fread(contents, buffsize + 1, 1, src);
	// Guardamos (y devolvemos) la cantidad de bytes escritos en la operacion.
	int written = fwrite(contents, buffsize, 1, dest);
	return written;
}


int main(int argc, char **argv) {
	size_t bufsize = atol(argv[1]);  // Tamaño a guardar
	char *src_path = malloc(strlen(argv[2])), // Ruta del archivo fuente
		 *dest_path = malloc(strlen(argv[3])); // Ruta del archivo destino
	strcpy(src_path, argv[2]); // Copiamos las rutas a partir de los argumentos
	strcpy(dest_path, argv[3]);
	FILE *src, *dest; // Punteros de archivos

	// Determinamos si la ruta fuente corresponde a un archivo.
	if (is_reg_file(src_path)) {
		// Abrimos el archivo fuente para lectura binaria
		src = fopen(src_path, "rb");
		// Abrimos el archivo destino para escritura binaria
		dest = fopen(dest_path, "wb");
		// Procedemos si pudimos abrir ambos ficheros
		if (src && dest) {
			// Realizamos la copia
			copyfile(src, dest, bufsize);
			// Cerramos los punteros
			fclose(src);
			fclose(dest);
		} else {
			// Si no pudimos abrir alguno, digamos cual
			printf("No pude abrir alguno de los dos archivos: src: %i, dest: %i\n", src != NULL, dest != NULL);
			return 1;
		}
	}

	// Liberamos memoria de los strings
	free(src_path); free(dest_path);

	return 0;
}