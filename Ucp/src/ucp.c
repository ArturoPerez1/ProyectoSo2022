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

int copyfile(FILE *src, FILE *dest, size_t buffsize) {
	void *contents = malloc(buffsize);
	fread(contents, buffsize + 1, 1, src);
	int written = fwrite(contents, buffsize, 1, dest);
	return written;
}


int main(int argc, char **argv) {
	size_t bufsize = atol(argv[1]);
	char *src_path = malloc(strlen(argv[2])), 
		 *dest_path = malloc(strlen(argv[3]));
	strcpy(src_path, argv[2]);
	strcpy(dest_path, argv[3]);
	FILE *src, *dest;
	if (is_reg_file(src_path)) {
		src = fopen(src_path, "r");
		dest = fopen(dest_path, "w");
		if (src && dest) {
			copyfile(src, dest, bufsize);
			fclose(src);
			fclose(dest);
		} else {
			printf("No pude abrir alguno de los dos archivos: src: %i, dest: %i\n", src != NULL, dest != NULL);
		}
	}

	free(src_path); free(dest_path);

	return 0;
}