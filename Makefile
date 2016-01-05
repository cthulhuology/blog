all : server http


server : server.c
	gcc -o server server.c

http : http.c
	gcc -o http http.c

.PHONY: clean
clean:
	rm server http
