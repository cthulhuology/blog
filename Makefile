all :  dev

.PHONY: dev prod

dev:
	CFLAGS=
	$(MAKE) server
	$(MAKE) http
	$(MAKE) md
	$(MAKE) blog

prod: clean
	CFLAGS=-O3 $(MAKE) server
	CFLAGS=-O3 $(MAKE) http
	CFLAGS=-O3 $(MAKE) md
	CFLAGS=-O3 $(MAKE) blog

server : server.c
	gcc $(CFLAGS) -o server server.c

http : http.c str.c parse.c
	gcc $(CFLAGS) -DHTTP -o http http.c str.c parse.c

md : md.c str.c parse.c html.c
	gcc $(FLAGS) -DMD -o md md.c str.c parse.c html.c

blog : blog.c http.c str.c parse.c file.c
	gcc $(CFLAGS) -DBLOG -o blog blog.c http.c str.c parse.c file.c

mkpath: dir.c str.c list.c
	gcc $(CFLAGS) -o mkpath -DDIRTOOLS dir.c list.c str.c

lspath: dir.c str.c list.c
	gcc -ggdb $(CFLAGS) -o lspath -DDIRTOOLS dir.c list.c str.c

generate: generate.c dir.c str.c list.c
	gcc -ggdb $(CFLAGS) -o generate -DGENERATE generate.c dir.c list.c str.c

.PHONY: clean
clean:
	rm -f server http md


.PHONY: test tests
	
test:
	cd test && $(MAKE)

tests:
	cd test && $(MAKE)
