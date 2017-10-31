all :  dev

.PHONY: dev prod publish tables

install:  monitor server blog
	cp monitor server blog ~/bin/

tables: 
	iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8080

run:
	./monitor ./server ./blog

login:
	$$(aws ecr get-login --no-include-email --region eu-central-1 )
publish:
	./generate
	docker build -t cthulhuology .
	docker tag -f cthulhuology:latest 754019368417.dkr.ecr.eu-central-1.amazonaws.com/cthulhuology:latest 
	docker push 754019368417.dkr.ecr.eu-central-1.amazonaws.com/cthulhuology:latest

CFLAGS=-static -DLINUX

dev:
	$(MAKE) monitor
	$(MAKE) server
	$(MAKE) http
	$(MAKE) md
	$(MAKE) blog

prod: clean
	CFLAGS=-static -O3 $(MAKE) monitor
	CFLAGS=-static -O3 $(MAKE) server
	CFLAGS=-static -O3 $(MAKE) http
	CFLAGS=-static -O3 $(MAKE) md
	CFLAGS=-static -O3 $(MAKE) blog
	CFLAGS=-static -O3 $(MAKE) generate
	CFLAGS=-static -O3 $(MAKE) lspath
	CFLAGS=-static -O3 $(MAKE) mkpath

monitor: monitor.c
	gcc $(CFLAGS) -o monitor monitor.c

server : server.c
	gcc $(CFLAGS) -o server server.c

http : http.c str.c parse.c
	gcc $(CFLAGS) -DHTTP -o http http.c str.c parse.c

md : md.c str.c parse.c html.c file.c
	gcc $(FLAGS) -DMD -o md md.c str.c parse.c html.c file.c

blog : blog.c http.c str.c parse.c file.c
	gcc $(CFLAGS) -DBLOG -o blog blog.c http.c str.c parse.c file.c

mkpath: dir.c str.c list.c
	gcc $(CFLAGS) -o mkpath -DDIRTOOLS dir.c list.c str.c

lspath: dir.c str.c list.c
	gcc -ggdb $(CFLAGS) -o lspath -DDIRTOOLS dir.c list.c str.c

generate: generate.c dir.c str.c list.c worker.c file.c
	gcc -ggdb $(CFLAGS) -o generate -DGENERATE generate.c dir.c list.c str.c worker.c file.c


worker: worker.c file.c str.c
	gcc -DWORKER -o worker worker.c file.c str.c

echo: echo.c
	gcc -o echo echo.c


.PHONY: clean
clean:
	rm -f server http md blog monitor generate echo worker lspath mkpath 


.PHONY: test tests
	
test:
	cd test && $(MAKE)

tests:
	cd test && $(MAKE)
