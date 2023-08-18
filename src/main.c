#define _GNU_SOURCE

#include <assert.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <drm/drm_fourcc.h>
#include <linux/udmabuf.h>

#include <libpng16/png.h>

#include "glad/egl.h"
#include "glad/gles2.h"

// Create a memfd-backed dmabuf
//
// Requires access to /dev/udmabuf (generally being a member of the kvm group)
int create_udmabuf(int size) {
	int udmabuf_dev = open("/dev/udmabuf", O_RDWR | O_CLOEXEC);
	assert(udmabuf_dev != -1);

	int memfd = memfd_create("test-udmabuf", MFD_CLOEXEC | MFD_ALLOW_SEALING);
	assert(memfd != -1);
	assert(ftruncate(memfd, size) != -1);
	assert(fcntl(memfd, F_ADD_SEALS, F_SEAL_SHRINK) != -1);

	struct udmabuf_create create;
	create.memfd = memfd;
	create.flags = UDMABUF_FLAGS_CLOEXEC;
	create.offset = 0;
	create.size = size;
	int udmabuf = ioctl(udmabuf_dev, UDMABUF_CREATE, &create);
	assert(udmabuf != -1);

	close(udmabuf_dev);
	close(memfd);

	return udmabuf;
}

void set_test_image(int fd, int width, int height, int stride) {
	char *bytes = mmap(NULL, stride * height, PROT_WRITE, MAP_SHARED, fd, 0);
	assert(bytes != NULL);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			char *color = bytes + y * stride + x * 4;
			if (((x / 8) % 2) == 0)
				color[0] = 255;
			else
				color[0] = 0;
			color[1] = 0;
			color[2] = 0;
			color[3] = 255;
		}
	}
	assert(munmap(bytes, stride * height) == 0);
}

// Import single-plane dmabuf as an EGLImage, and create an OpenGL texture
GLuint bind_dmabuf(EGLDisplay display, EGLAttrib width, EGLAttrib height, EGLAttrib fourcc, EGLAttrib fd, EGLAttrib offset, EGLAttrib pitch) {
	// XXX modifier??
	EGLAttrib attrs[] = {
		EGL_WIDTH, width,
		EGL_HEIGHT, height,
		EGL_LINUX_DRM_FOURCC_EXT, fourcc,
		EGL_DMA_BUF_PLANE0_FD_EXT, fd,
		EGL_DMA_BUF_PLANE0_OFFSET_EXT, offset,
		EGL_DMA_BUF_PLANE0_PITCH_EXT, pitch,
		EGL_NONE
	};
	EGLImage image = eglCreateImage(display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, attrs); 
	assert(image !=  EGL_NO_IMAGE);

	assert(glGetError() == GL_NO_ERROR);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
	glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, image);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);

	eglDestroyImage(display, image);

	if (glGetError() != GL_NO_ERROR)
		printf("Import failed\n");
	else
		printf("Import Succeeded\n");

	return texture;
}

GLuint compile_shader(GLenum shaderType, const char *src) {
	GLuint shader = glCreateShader(shaderType);
	GLint length = strlen(src);
	glShaderSource(shader, 1, &src, &length);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(compiled == GL_FALSE) {
		GLint log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		char *log = malloc(log_length + 1);
		glGetShaderInfoLog(shader, log_length, &log_length, log);
		printf("Shader error: %s", log);
		exit(1);
	}

	return shader;
}

GLuint shader_program(const char *vs_src, const char *fs_src) {
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vs_src);
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fs_src);
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	assert(linked == GL_TRUE);

	return program;
}

void write_png(char *buffer, png_uint_32 width, png_uint_32 height, char *path) {
	png_image img;
	memset(&img, 0, sizeof(img));
	img.version = PNG_IMAGE_VERSION;
	img.width = width;
	img.height = height;
	img.format = PNG_FORMAT_RGBA;
	png_image_write_to_file(&img, path, 0, buffer, 0, NULL);
	png_image_free(&img);
}

// Use simple shaders to draw texture to framebuffer with a sampler
void draw_texture_to_framebuffer(GLuint texture, int width, int height) {
	glGetError();
	// TODO render texture to framebuffer?
	const char *vs =
		"#version 100\n"
		"attribute vec4 vertex;\n"
		"varying highp vec2 tex_coord;\n"
		"void main(void) {\n"
		"	gl_Position = (vec4(2.0, 2.0, 1.0, 1.0) * vertex) - vec4(1.0, 1.0, 0.0, 0.0);\n"
		"	tex_coord = vertex.xy;\n" 
		"}\n";
	// XXX tex coords
	const char *fs =
		"#version 100\n"
		"#extension GL_OES_EGL_image_external : enable\n"
		"uniform samplerExternalOES sampler;\n"
		"varying highp vec2 tex_coord;\n"
		"void main(void) {\n"
		"	gl_FragColor = texture2D(sampler, tex_coord);\n"
		"}\n";
	GLuint program = shader_program(vs, fs);
	glUseProgram(program);

	GLuint vertex_attrib = glGetAttribLocation(program, "vertex");
	GLuint sampler_uniform = glGetUniformLocation(program, "sampler");
	assert(vertex_attrib != -1);
	assert(sampler_uniform != -1);

	GLfloat vertices[10];
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 1;
	vertices[3] = 0;
	vertices[4] = 0;
	vertices[5] = 1;
	vertices[6] = 1;
	vertices[7] = 1;
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(vertex_attrib);
   	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertices, GL_STATIC_DRAW);
   	glVertexAttribPointer(vertex_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(sampler_uniform, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // XXX

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
	glDeleteProgram(program);

	assert(glGetError() == GL_NO_ERROR);
}

int main() {
	int dmabuf = create_udmabuf(256 * 256 * 4);
	set_test_image(dmabuf, 256, 256, 256 * 4);

	void *libegl = dlopen("libEGL.so.1", RTLD_LAZY);
	assert(libegl != NULL);
	GLADloadfunc eglLoader = dlsym(libegl, "eglGetProcAddress");

	int egl_version = gladLoadEGL(NULL, eglLoader);
	assert(egl_version != 0);
	const char *version = eglQueryString(EGL_NO_DISPLAY, EGL_VERSION);	
	printf("Loaded EGL %s\n", version);

	assert(GLAD_EGL_EXT_device_enumeration);
	assert(GLAD_EGL_EXT_platform_device);
	
	EGLint n_devices = 0;
	EGLDeviceEXT devices[16];
	eglQueryDevicesEXT(16, devices, &n_devices);
	printf("%d devices\n", n_devices);
	for (int i = 0; i < n_devices; i++) {
		EGLDisplay display = eglGetDisplay(devices[i]);
		assert(display != EGL_NO_DISPLAY);

		//assert(eglInitialize(display, NULL, NULL));
		if (!eglInitialize(display, NULL, NULL))
			continue;
		assert(gladLoadEGL(display, eglLoader) != 0);
		assert(eglBindAPI(EGL_OPENGL_ES_API));

		const char *vendor = eglQueryString(display, EGL_VENDOR);
		if (GLAD_EGL_MESA_query_driver) {
			const char *driver = eglGetDisplayDriverName(display);
			printf("driver: %s; %s\n", vendor, driver);
		} else {
			printf("driver: %s\n", vendor);
		}

		//const char *extensions = eglQueryString(display, EGL_EXTENSIONS);
		//printf("Extensions: %s\n", extensions);
		if (!GLAD_EGL_EXT_image_dma_buf_import || !GLAD_EGL_MESA_image_dma_buf_export) {
			continue;
		}

		EGLint n_configs, n_chosen_configs;
		assert(eglGetConfigs(display, NULL, 0, &n_configs) != 0 && n_configs > 0);
		EGLConfig *configs = malloc(n_configs * sizeof(EGLConfig));
		// XXX attribs
		assert(eglGetConfigs(display, configs, n_configs, &n_chosen_configs) != 0);
		//assert(eglChooseConfig(display, NULL, configs, n_configs, &n_chosen_configs) != 0 && n_chosen_configs > 0);
		EGLint surfaceAttributes[] = {
			EGL_WIDTH, 256,
			EGL_HEIGHT, 256,
			EGL_NONE
		};
		EGLSurface surface = eglCreatePbufferSurface(display, configs[0], surfaceAttributes);
		assert(surface != EGL_NO_SURFACE);
		EGLint contextAttributes[] = {
			EGL_CONTEXT_MAJOR_VERSION, 2,
			EGL_NONE
		};
		EGLContext context = eglCreateContext(display, configs[0], EGL_NO_CONTEXT, contextAttributes);
		assert(context != EGL_NO_CONTEXT);
		assert(eglMakeCurrent(display, surface, surface, context));

		int gles_version = gladLoadGLES2(eglGetProcAddress);
		assert(gles_version != 0);
		printf("Loaded GLES %d.%d\n", GLAD_VERSION_MAJOR(gles_version), GLAD_VERSION_MINOR(gles_version));

		assert(GLAD_GL_OES_EGL_image_external);

		GLuint texture = bind_dmabuf(display, 256, 256, DRM_FORMAT_ARGB8888, dmabuf, 0, 256 *4);

		// TODO render texture to framebuffer?
		draw_texture_to_framebuffer(texture, 256, 256);

		// XXX bind read fb
		char data[256 * 256 * 4];
		glReadPixels(0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, &data);
		char *filename = NULL;
		asprintf(&filename, "test%d.png", i);
		write_png(data, 256, 256, filename);
		free(filename);
	}
}
