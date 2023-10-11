egl-dmabuf-test: src/*.c
	gcc -Wall -o $@ -I include $^ -lpng

run: egl-dmabuf-test
	./egl-dmabuf-test

clean:
	rm egl-dmabuf-test

.PHONY: run clean
