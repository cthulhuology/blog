all :  dev

.PHONY: dev prod

dev:
	CFLAGS=
	$(MAKE) server
	$(MAKE) http
	$(MAKE) md

prod: clean
	CFLAGS=-O3 $(MAKE) server
	CFLAGS=-O3 $(MAKE) http
	CFLAGS=-O3 $(MAKE) md

server : server.c
	gcc $(CFLAGS) -o server server.c

http : http.c str.c parse.c
	gcc $(CFLAGS) -o http http.c str.c parse.c

md : md.c str.c parse.c html.c
	gcc $(FLAGS) -o md md.c str.c parse.c html.c

.PHONY: clean
clean:
	rm -f server http md


.PHONY: test tests
	
test:
	cd test && $(MAKE)

tests:
	cd test && $(MAKE)
