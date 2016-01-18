// server.c
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

////////////////////////////////////////////////////////////////////////////////
// headers
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

////////////////////////////////////////////////////////////////////////////////
// defines

////////////////////////////////////////////////////////////////////////////////
// globals
int done = 0;	// set if the main loop is to be terminated

////////////////////////////////////////////////////////////////////////////////
// functions

// usage
// 	prints out a usage message if the two parameters aren't passed
//
void usage(int argc, char** argv) {
	if (argc == 4) return; 
	fprintf(stderr,"%s: host port service\n", argv[0]);
	exit(0);
}

// error
//	prints an error message and exits with status non-zero
//
void error(char* message) {
	fprintf(stderr,"%s\n", message);
	exit(1);
}

// lookup 
// 	finds the host and port's inet info
// 	this function is IPv4/6 agnostic
//	freeaddrinfo the resulting struct when you're done
//
struct addrinfo* lookup(char* host, char* port) {
	struct addrinfo pre, *post;
	pre.ai_flags = AI_PASSIVE;
	pre.ai_family = AF_UNSPEC;
	pre.ai_socktype = SOCK_STREAM;
	pre.ai_protocol = IPPROTO_TCP;
	if (0 == getaddrinfo(host,port,&pre,&post))
		return post;
	return NULL;
}

// serve
//	takes the addrinfo returned by lookup and
//	listens on the port returning a socket
//
int serve(struct addrinfo* server) {
	int flags;
	int fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
	if (fd < 0) error("Failed to create server socket");
	flags = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags))) error("Failed to set reuseaddr flag");
	flags = fcntl(fd,F_GETFL,0);
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK)) error("Failed to set nonblocking flag on socket");
	if (bind(fd, server->ai_addr, server->ai_addrlen)) error("Failed to bind to address");
	return fd;	
}


// reap
//	collects child processes
void reap() {
	int pid, status = 0;
	pid = waitpid(-1,&status,WNOHANG); 
	if (pid < 0) return;
	if (pid && status) fprintf(stderr,"Child %d exited with status %d\n", pid, status);
}

// process
//	forks off a child process that provides the associated service
//
void process(int client, char* service) {
	char *args[] = { service, NULL };
	if (!fork()) {
		// in child
		close(0);
		close(1);
		dup2(client,0);	// set client socket to stdin
		dup2(client,1);	// set client socket to stdout
		if (execvp(service,args)) error("Failed to spawn service"); // run the supplied service
		exit(0);	// if we failed to spawn, kill child
	}
}

// monitor
//	waits on the socket until there's activity 
//	and then forks off a process to handle the connection
//
void monitor(int sock, char* service) {
	int fd, active = 0, client;
	struct epoll_event ev;
	struct sockaddr client_addr;
	socklen_t client_addr_len;
	if (listen(sock,128)) error("Failed to listen on socket");	// cf.  /proc/sys/net/core/somaxconn
	fd = epoll_create(1);
	ev.events = EPOLLIN;
	ev.data.fd = sock;
	if (epoll_ctl(fd,EPOLL_CTL_ADD,sock,&ev)) error("Failed to epoll socket");
	while(!done) {
		if ((active = epoll_wait(fd,&ev,1,100)) < 0) error("Failed to wait for socket activity");
		if (active > 0) {
			client = accept(sock,&client_addr,&client_addr_len);
 			if (client) process(client,service);
		}
		reap();
	}
}


// main 
//
int main (int argc, char** argv) {
	usage(argc,argv);
	struct addrinfo* server = lookup(argv[1],argv[2]);
	int sock = serve(server);
	printf("serve %ld\n", getpid());
	monitor(sock,argv[3]);
	freeaddrinfo(server);	// free structure returned by lookup
	return 0;
}
