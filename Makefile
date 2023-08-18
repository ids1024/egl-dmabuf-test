test: src/*.c
	gcc -Wall -o $@ -I include $^ -lpng16

run: test
	./test

.PHONY: run
