test: src/*.c
	gcc -Wall -lpng16 -o $@ -I include $^

run: test
	./test

.PHONY: run
