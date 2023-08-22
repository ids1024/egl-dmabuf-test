egl-dmabuf-test: src/*.c
	gcc -Wall -o $@ -I include $^ -lpng16

run: egl-dmabuf-test
	./egl-dmabuf-test

.PHONY: run
