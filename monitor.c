// monitor.c
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

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int server = 0;

void restart(int s) {
	if (server) kill(server,SIGHUP);		// propagate the HUP
}

void done(int s) {
	if (server) kill(server,SIGQUIT);		// then kill everybody
	exit(0);
}

int main(int argc, char** argv) {
	char* process;
	char** args;
	int status;
	int delay = 1;

	if (argc < 2) return 0;

	process = argv[1];
	args = argv + 1;	// skip monitor

	// restart on HUP
	signal(SIGHUP,restart);

	// otherwise kill all
	signal(SIGINT,done);
	signal(SIGQUIT,done);
	signal(SIGTERM,done);
	
	while(1) {
		fprintf(stderr,"Spawing %s\n", process);
		if (server = fork()) waitpid(server,&status,0);
		else execvp(process,args);
		sleep(delay);		// don't restart more than once a second
	}	
	// never get here
}
