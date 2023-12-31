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
    int page_size = getpagesize();
    while (size % page_size != 0)
        size++;

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

// Writes image data, as RGBA, containing vertical red/blue/green stripes.
void set_test_image(char *bytes, int width, int height, int stride) {
    const int STRIPE_WIDTH = 9;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char *color = bytes + y * stride + x * 4;
            int stripe = ((x / STRIPE_WIDTH) % 3);
            color[0] = 255 * (stripe == 0);
            color[1] = 255 * (stripe == 1);
            color[2] = 255 * (stripe == 2);
            color[3] = 255;
        }
    }
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
    if(image ==  EGL_NO_IMAGE)
        return 0;

    assert(glGetError() == GL_NO_ERROR);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, image);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);

    eglDestroyImage(display, image);

    if (glGetError() != GL_NO_ERROR) {
        glDeleteTextures(1, &texture);
        return 0;
    }

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

void write_png(char *buffer, int width, int height, int stride, char *path) {
    png_image img;
    memset(&img, 0, sizeof(img));
    img.version = PNG_IMAGE_VERSION;
    img.width = width;
    img.height = height;
    img.format = PNG_FORMAT_RGBA;
    png_image_write_to_file(&img, path, 0, buffer, stride, NULL);
    png_image_free(&img);
}

// Use simple shaders to draw texture to framebuffer with a sampler
void draw_texture_to_framebuffer(GLuint texture, int width, int height) {
    glGetError();
    const char *vs =
        "#version 100\n"
        "attribute vec4 vertex;\n"
        "varying highp vec2 tex_coord;\n"
        "void main(void) {\n"
        "    gl_Position = (vec4(2.0, 2.0, 1.0, 1.0) * vertex) - vec4(1.0, 1.0, 0.0, 0.0);\n"
        "    tex_coord = vertex.xy;\n" 
        "}\n";
    const char *fs =
        "#version 100\n"
        "#extension GL_OES_EGL_image_external : enable\n"
        "uniform samplerExternalOES sampler;\n"
        "varying highp vec2 tex_coord;\n"
        "void main(void) {\n"
        "    gl_FragColor = texture2D(sampler, tex_coord);\n"
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
    glUniform1i(sampler_uniform, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glUseProgram(0);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
    glDeleteProgram(program);

    assert(glGetError() == GL_NO_ERROR);
}

// Returns 1 if image have same pixels
int image_matches(int width, int height, char *image1, int stride1, char *image2, int stride2) {
    for (int y = 0; y < height; y++) {
        for (int b = 0; b < width * 4; b++) {
            if (image1[y * stride1 + b] != image2[y * stride2 + b])
                return 0;
        }
    }
    return 1;
}

// Run tests for display at given size. Requires bound gl context.
void test_gl_size(EGLDisplay display, char *device_name, int width, int height, int stride) {
    int dmabuf = create_udmabuf(stride * height);
    char *dmabuf_bytes = mmap(NULL, stride * height, PROT_WRITE, MAP_SHARED, dmabuf, 0);
    assert(dmabuf_bytes != NULL);
    set_test_image(dmabuf_bytes, width, height, stride);
    char *filename = NULL;
    asprintf(&filename, "reference-%dx%d-%d.png", width, height, stride);
    write_png(dmabuf_bytes, width, height, stride, filename);
    free(filename);

    GLuint renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8_OES, width, height);
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    glViewport(0, 0, width, height);

    GLuint texture = bind_dmabuf(display, width, height, DRM_FORMAT_ABGR8888, dmabuf, 0, stride);

    int matches = 0;
    if (texture != 0) {
        draw_texture_to_framebuffer(texture, width, height);

        char *data = malloc(height * width * 4);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        if (image_matches(width, height, dmabuf_bytes, stride, data, width * 4))
            matches = 1;

        filename = NULL;
        asprintf(&filename, "%s-%dx%d-%d.png", device_name, width, height, stride);
        write_png(data, width, height, 0, filename);
        free(data);
        free(filename);
    }

    printf("    %dx%d at stride %d: ", width, height, stride);
    if (matches)
        printf("success\n");
    else if (texture)
        printf("failed to match expected output\n");
    else
        printf("import failed\n");

    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteRenderbuffers(1, &renderbuffer);
    assert(munmap(dmabuf_bytes, stride * height) == 0);
    close(dmabuf);
}

void test_egl(EGLDisplay display, char *device_name) {
    assert(eglBindAPI(EGL_OPENGL_ES_API));

    const char *driver_name;
    if (GLAD_EGL_MESA_query_driver) {
        driver_name = eglGetDisplayDriverName(display);
    } else {
        driver_name = eglQueryString(display, EGL_VENDOR);
    }

    if (!GLAD_EGL_EXT_image_dma_buf_import || !GLAD_EGL_MESA_image_dma_buf_export || !GLAD_EGL_KHR_surfaceless_context) {
        return;
    }

    EGLint n_configs, n_chosen_configs;
    assert(eglGetConfigs(display, NULL, 0, &n_configs) != 0 && n_configs > 0);
    EGLConfig *configs = malloc(n_configs * sizeof(EGLConfig));
    EGLint configAttributes[] = {
        EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_NONE,
    };
    assert(eglChooseConfig(display, configAttributes, configs, n_configs, &n_chosen_configs) != 0);
    assert(n_chosen_configs > 0);

    EGLint contextAttributes[] = {
        EGL_CONTEXT_MAJOR_VERSION, 2,
        EGL_NONE
    };
    EGLContext context = eglCreateContext(display, configs[0], EGL_NO_CONTEXT, contextAttributes);
    assert(context != EGL_NO_CONTEXT);
    assert(eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context));

    int gles_version = gladLoadGLES2(eglGetProcAddress);
    assert(gles_version != 0);

    printf("%s (%s, GLES %d.%d)\n", device_name, driver_name, GLAD_VERSION_MAJOR(gles_version), GLAD_VERSION_MINOR(gles_version));

    assert(GLAD_GL_OES_EGL_image_external);

    test_gl_size(display, device_name, 256, 256, 256 * 4);
    test_gl_size(display, device_name, 255, 256, 256 * 4);
    test_gl_size(display, device_name, 255, 256, 255 * 4);
    test_gl_size(display, device_name, 254, 256, 254 * 4);
    test_gl_size(display, device_name, 252, 256, 252 * 4);
}

int main() {
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
    for (int i = 0; i < n_devices; i++) {
        EGLDisplay display = eglGetDisplay(devices[i]);
        assert(display != EGL_NO_DISPLAY);

        if (!eglInitialize(display, NULL, NULL))
            continue;

        assert(gladLoadEGL(display, eglLoader) != 0);

        const char *device_file = eglQueryDeviceStringEXT(devices[i], EGL_DRM_DEVICE_FILE_EXT);
        if(device_file == NULL)
            continue;

        test_egl(display, basename(device_file));
    }
}
