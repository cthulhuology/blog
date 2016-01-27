// worker.c
//
// Copyright (C) 2016 David J. Goehrig
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//

#include "worker.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "file.h"

int running = 0;
int run(char* service, int in, int out, char** args) {
	++running;
	int c;
	if (c = fork()) return c; 
	// in child
	if (in != 0) close(0);
	if (out != 1) close(1);
	dup2(in,0);	// set in fd to stdin
	dup2(out,1);	// set out fd to stdout
	if (execvp(service,args)) fprintf(stderr,"Failed to spawn %s\n", service); // run the supplied service
	exit(0);	// if we failed to spawn, kill child
}

int done = 1;
void reap() {
	int status = 0;
	int pid = 0;
	while(running) {	
		pid = waitpid(-1,&status,0);	 // WNOHANG 
		if (pid < 0) return;
		if (pid && status) {
			fprintf(stderr,"%d exited with status %d\n", pid,status);
		}
		if (pid) --running;
	}
}

#ifdef WORKER

int main(int argc, char** argv) {
	char* a[] = { "a", NULL };	
	char* b[] = { "b", NULL };	
	char* c[] = { "c", NULL };	

//	int i = input("worker.c");
//	int o = output("worker.txt");

	int i = 0;
	int o = 1;
	
	run("./echo", i, o, a);
	run("./echo", i, o, b);
	run("./echo", i, o, c);
	reap();
	return 0;
}

#endif
