#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_reg_file(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

int copyfile(FILE *src, FILE *dest, int buffsize) {
	void *contents;
	printf("%s\n", "Antes de leer");
	fread(contents, buffsize, 1, src);
	printf("Luego de leer\n");
	printf("%s\n", (char *)contents);
	printf("%s\n", "Antes de escribir contenidos en el destino");
	int written = fwrite(contents, buffsize, 1, dest);
	printf("%s\n", "Luego de escribir contenidos en el destino");
	return written;
}


int main(int argc, char **argv) {
	size_t bufsize = atol(argv[1]);
	char *src_path = argv[2], *dest_path = argv[3];
	FILE *src, *dest;
	if (is_reg_file(src_path)) {
		src = fopen(src_path, "r");
		dest = fopen(dest_path, "w");
		if (src && dest) {
			copyfile(src, dest, bufsize);
			fclose(src);
			fclose(dest);
		}
	}

	return 0;
}