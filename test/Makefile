CFLAGS=-I. -I../ -DTEST

.PHONY: test render
test: all

all: test_parse test_http test_md render

test_parse: test_parse.c ../parse.c ../test.c ../test.h 
	gcc $(CFLAGS) -o test_parse test_parse.c ../parse.c ../test.c
	./test_parse
	rm test_parse

test_http: test_http.c ../http.c ../parse.c ../test.c ../test.h ../str.c
	gcc $(CFLAGS) -DMAX_HEADERS=3 -o test_http test_http.c ../http.c ../parse.c ../test.c ../str.c
	./test_http
	rm test_http

test_md: test_md.c ../md.c ../parse.c ../test.c ../test.h ../str.c ../html.c
	gcc $(CFLAGS) -o test_md test_md.c ../md.c ../parse.c ../test.c ../str.c ../html.c
	./test_md
	rm test_md

test_list: test_list.c ../list.c ../str.c ../test.h ../test.c ../list.h ../str.h
	gcc $(CFLAGS) -o test_list test_list.c ../list.c ../str.c ../test.c


render:
	cd render && $(MAKE) test

.PHONY: clean
clean:
	rm test_parse
