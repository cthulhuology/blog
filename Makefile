all : server


server : server.c
	gcc -o server server.c

.PHONY: clean
clean:
	rm server
