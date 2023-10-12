#include <assert.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gbm.h>

#include "glad/egl.h"
#include "glad/gles2.h"

struct gbm_device *open_gbm_device(char *path) {
    printf("Opening gbm device for %s\n", path);
    int fd = open(path, O_RDWR);
    assert(fd != 0);
    struct gbm_device *gbm = gbm_create_device(fd);
    assert(gbm != NULL);
    return gbm;
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
    // glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
    // glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, image);
    // glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glad_glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, image);
    glBindTexture(GL_TEXTURE_2D, 0);

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

void init_gles(EGLDisplay display) {
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
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
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

    printf("Loaded OpenGL (%s, GLES %d.%d)\n", driver_name, GLAD_VERSION_MAJOR(gles_version), GLAD_VERSION_MINOR(gles_version));

    assert(GLAD_GL_OES_EGL_image_external);
}

int main() {
    void *libegl = dlopen("libEGL.so.1", RTLD_LAZY);
    assert(libegl != NULL);
    GLADloadfunc eglLoader = dlsym(libegl, "eglGetProcAddress");

    int egl_version = gladLoadEGL(NULL, eglLoader);
    assert(egl_version != 0);
    const char *version = eglQueryString(EGL_NO_DISPLAY, EGL_VERSION);    
    printf("Loaded EGL %s\n", version);

    struct gbm_device *gbm1 = open_gbm_device("/dev/dri/renderD128");
    // EGLAttrib attribs[] = { EGL_NONE };
    // EGLDisplay display = eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR, gbm1, attribs);
    EGLDisplay display = eglGetDisplay(gbm1);
    assert(display != EGL_NO_DISPLAY);
    assert(eglInitialize(display, NULL, NULL));
    assert(gladLoadEGL(display, eglLoader) != 0);

    init_gles(display);

    struct gbm_device *gbm2 = open_gbm_device("/dev/dri/renderD129");
    struct gbm_bo *bo = gbm_bo_create(gbm2, 1920, 1080, GBM_FORMAT_ABGR8888, GBM_BO_USE_LINEAR);
    assert(bo != NULL);
    int fd = gbm_bo_get_fd(bo);
    assert(fd != -1);
    uint32_t stride = gbm_bo_get_stride(bo);
    gbm_bo_destroy(bo);
    gbm_device_destroy(gbm2);

    GLuint texture = bind_dmabuf(display, 1920, 1080, GBM_FORMAT_ABGR8888, fd, 0, stride);

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glBindTexture(GL_TEXTURE_2D, texture);
    assert(glGetError() == GL_NO_ERROR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    const char *vs =
        "#version 100\n"
        "attribute vec4 vertex;\n"
        "void main(void) {\n"
        "    gl_Position = (vec4(2.0, 2.0, 1.0, 1.0) * vertex) - vec4(1.0, 1.0, 0.0, 0.0);\n"
        "}\n";
    const char *fs =
        "#version 100\n"
        "void main(void) {\n"
        "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    GLuint program = shader_program(vs, fs);
    glUseProgram(program);

    GLuint vertex_attrib = glGetAttribLocation(program, "vertex");
    assert(vertex_attrib != -1);

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

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glUseProgram(0);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
    glDeleteProgram(program);

    assert(glGetError() == GL_NO_ERROR);

}
