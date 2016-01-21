all: test


.PHONY: test clean
test:
	@echo "Rendering Tests"
	@cat test1.md | ../../md > test1.html
	@cat test2.md | ../../md > test2.html
	@cat test3.md | ../../md > test3.html
	@cat test4.md | ../../md > test4.html
	@./check test1.html test1.target
	@./check test2.html test2.target
	@./check test3.html test3.target
	@./check test4.html test4.target
	@rm *.html

clean:
	@rm *.html
