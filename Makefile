all : server http


server : server.c
	gcc -o server server.c

http : http.c str.c parse.c
	gcc -o http http.c str.c parse.c

.PHONY: clean
clean:
	rm server http


.PHONY: test tests
	
test:
	cd test && $(MAKE)

tests:
	cd test && $(MAKE)
