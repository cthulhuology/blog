all :  dev

.PHONY: dev prod

dev:
	CFLAGS=
	$(MAKE) server
	$(MAKE) http

prod: clean
	CFLAGS=-O3 $(MAKE) server
	CFLAGS=-O3 $(MAKE) http

server : server.c
	gcc $(CFLAGS) -o server server.c

http : http.c str.c parse.c
	gcc $(CFLAGS) -o http http.c str.c parse.c

.PHONY: clean
clean:
	rm server http


.PHONY: test tests
	
test:
	cd test && $(MAKE)

tests:
	cd test && $(MAKE)
