all: test


.PHONY: test
test:
	@cat test1.md | ../../md > test1.html
	@cat test2.md | ../../md > test2.html
	@cat test3.md | ../../md > test3.html
	@./check test1.html test1.target
	@./check test2.html test2.target
	@./check test3.html test3.target

clean:
	rm *.html
