#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
	struct rlimit rlim;
	getrlimit(RLIMIT_NPROC, &rlim);
	printf("%lu\n", rlim.rlim_max);
}
