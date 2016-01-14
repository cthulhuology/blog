
CFLAGS=-I. -I../ -DTEST

all: test_parse test_http

test_parse: test_parse.c ../parse.c ../test.c ../test.h 
	gcc $(CFLAGS) -o test_parse test_parse.c ../parse.c ../test.c
	./test_parse
	rm test_parse

test_http: test_http.c ../http.c ../parse.c ../test.c ../test.h 
	gcc $(CFLAGS) -o test_http test_http.c ../http.c ../parse.c ../test.c
	./test_http
	rm test_http


.PHONY: clean
clean:
	rm test_parse
