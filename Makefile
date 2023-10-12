egl-dmabuf-test: src/main.o src/gles2.o src/egl.o
	gcc -Wall -o $@ $^ -lpng

%.o: %.c
	gcc -c -Wall -o $@ -I include $^

run: egl-dmabuf-test
	./egl-dmabuf-test

clean:
	rm egl-dmabuf-test src/*.o

.PHONY: run clean
