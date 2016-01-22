// dir.c
//
//


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int mkpath(char* path) {
	size_t l = strlen(path);
	int i = 0;
	for (i = 0; i < l; ++i) {
		if (path[i] != '/') continue;
		path[i] = '\0';
		mkdir(path,0777);
		path[i] = '/';
	}
	return l;
}

#ifdef DIR

int main(int argc, char** argv) {
	if (argc == 1) return 0;
	mkpath(argv[1]);
	return 0;
}

#endif
