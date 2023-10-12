egl-dmabuf-test: src/main.o src/gles2.o src/egl.o
	gcc -g -Wall -o $@ $^ -lpng

test-external-framebuffer: src/test-external-framebuffer.o src/gles2.o src/egl.o
	gcc -g -Wall -o $@ $^ -lgbm

%.o: %.c
	gcc -g -c -Wall -o $@ -I include $^

run: egl-dmabuf-test
	./egl-dmabuf-test

clean:
	rm egl-dmabuf-test test-external-framebuffer src/*.o

.PHONY: run clean
