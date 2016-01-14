
CFLAGS=-I. -I../

all:

test_parse: test_parse.c ../parse.c ../test.c ../test.h 
	gcc $(CFLAGS) -o test_parse test_parse.c ../parse.c ../test.c
	./test_parse
	rm test_parse


.PHONY: clean
clean:
	rm test_parse
