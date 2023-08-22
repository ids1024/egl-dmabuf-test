/**
 * Loader generated by glad 2.0.4 on Mon Aug 21 21:10:09 2023
 *
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 *
 * Generator: C/C++
 * Specification: egl
 * Extensions: 8
 *
 * APIs:
 *  - egl=1.5
 *
 * Options:
 *  - ALIAS = False
 *  - DEBUG = False
 *  - HEADER_ONLY = False
 *  - LOADER = False
 *  - MX = False
 *  - ON_DEMAND = False
 *
 * Commandline:
 *    --api='egl=1.5' --extensions='EGL_EXT_device_drm,EGL_EXT_device_enumeration,EGL_EXT_device_query,EGL_EXT_image_dma_buf_import,EGL_EXT_image_dma_buf_import_modifiers,EGL_EXT_platform_device,EGL_MESA_image_dma_buf_export,EGL_MESA_query_driver' c
 *
 * Online:
 *    http://glad.sh/#api=egl%3D1.5&extensions=EGL_EXT_device_drm%2CEGL_EXT_device_enumeration%2CEGL_EXT_device_query%2CEGL_EXT_image_dma_buf_import%2CEGL_EXT_image_dma_buf_import_modifiers%2CEGL_EXT_platform_device%2CEGL_MESA_image_dma_buf_export%2CEGL_MESA_query_driver&generator=c&options=
 *
 */

#ifndef GLAD_EGL_H_
#define GLAD_EGL_H_


#define GLAD_EGL

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAD_PLATFORM_H_
#define GLAD_PLATFORM_H_

#ifndef GLAD_PLATFORM_WIN32
  #if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__)
    #define GLAD_PLATFORM_WIN32 1
  #else
    #define GLAD_PLATFORM_WIN32 0
  #endif
#endif

#ifndef GLAD_PLATFORM_APPLE
  #ifdef __APPLE__
    #define GLAD_PLATFORM_APPLE 1
  #else
    #define GLAD_PLATFORM_APPLE 0
  #endif
#endif

#ifndef GLAD_PLATFORM_EMSCRIPTEN
  #ifdef __EMSCRIPTEN__
    #define GLAD_PLATFORM_EMSCRIPTEN 1
  #else
    #define GLAD_PLATFORM_EMSCRIPTEN 0
  #endif
#endif

#ifndef GLAD_PLATFORM_UWP
  #if defined(_MSC_VER) && !defined(GLAD_INTERNAL_HAVE_WINAPIFAMILY)
    #ifdef __has_include
      #if __has_include(<winapifamily.h>)
        #define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
      #endif
    #elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
      #define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
    #endif
  #endif

  #ifdef GLAD_INTERNAL_HAVE_WINAPIFAMILY
    #include <winapifamily.h>
    #if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
      #define GLAD_PLATFORM_UWP 1
    #endif
  #endif

  #ifndef GLAD_PLATFORM_UWP
    #define GLAD_PLATFORM_UWP 0
  #endif
#endif

#ifdef __GNUC__
  #define GLAD_GNUC_EXTENSION __extension__
#else
  #define GLAD_GNUC_EXTENSION
#endif

#define GLAD_UNUSED(x) (void)(x)

#ifndef GLAD_API_CALL
  #if defined(GLAD_API_CALL_EXPORT)
    #if GLAD_PLATFORM_WIN32 || defined(__CYGWIN__)
      #if defined(GLAD_API_CALL_EXPORT_BUILD)
        #if defined(__GNUC__)
          #define GLAD_API_CALL __attribute__ ((dllexport)) extern
        #else
          #define GLAD_API_CALL __declspec(dllexport) extern
        #endif
      #else
        #if defined(__GNUC__)
          #define GLAD_API_CALL __attribute__ ((dllimport)) extern
        #else
          #define GLAD_API_CALL __declspec(dllimport) extern
        #endif
      #endif
    #elif defined(__GNUC__) && defined(GLAD_API_CALL_EXPORT_BUILD)
      #define GLAD_API_CALL __attribute__ ((visibility ("default"))) extern
    #else
      #define GLAD_API_CALL extern
    #endif
  #else
    #define GLAD_API_CALL extern
  #endif
#endif

#ifdef APIENTRY
  #define GLAD_API_PTR APIENTRY
#elif GLAD_PLATFORM_WIN32
  #define GLAD_API_PTR __stdcall
#else
  #define GLAD_API_PTR
#endif

#ifndef GLAPI
#define GLAPI GLAD_API_CALL
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY GLAD_API_PTR
#endif

#define GLAD_MAKE_VERSION(major, minor) (major * 10000 + minor)
#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)

#define GLAD_GENERATOR_VERSION "2.0.4"

typedef void (*GLADapiproc)(void);

typedef GLADapiproc (*GLADloadfunc)(const char *name);
typedef GLADapiproc (*GLADuserptrloadfunc)(void *userptr, const char *name);

typedef void (*GLADprecallback)(const char *name, GLADapiproc apiproc, int len_args, ...);
typedef void (*GLADpostcallback)(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...);

#endif /* GLAD_PLATFORM_H_ */

#define EGL_ALPHA_FORMAT 0x3088
#define EGL_ALPHA_FORMAT_NONPRE 0x308B
#define EGL_ALPHA_FORMAT_PRE 0x308C
#define EGL_ALPHA_MASK_SIZE 0x303E
#define EGL_ALPHA_SIZE 0x3021
#define EGL_BACK_BUFFER 0x3084
#define EGL_BAD_ACCESS 0x3002
#define EGL_BAD_ALLOC 0x3003
#define EGL_BAD_ATTRIBUTE 0x3004
#define EGL_BAD_CONFIG 0x3005
#define EGL_BAD_CONTEXT 0x3006
#define EGL_BAD_CURRENT_SURFACE 0x3007
#define EGL_BAD_DEVICE_EXT 0x322B
#define EGL_BAD_DISPLAY 0x3008
#define EGL_BAD_MATCH 0x3009
#define EGL_BAD_NATIVE_PIXMAP 0x300A
#define EGL_BAD_NATIVE_WINDOW 0x300B
#define EGL_BAD_PARAMETER 0x300C
#define EGL_BAD_SURFACE 0x300D
#define EGL_BIND_TO_TEXTURE_RGB 0x3039
#define EGL_BIND_TO_TEXTURE_RGBA 0x303A
#define EGL_BLUE_SIZE 0x3022
#define EGL_BUFFER_DESTROYED 0x3095
#define EGL_BUFFER_PRESERVED 0x3094
#define EGL_BUFFER_SIZE 0x3020
#define EGL_CLIENT_APIS 0x308D
#define EGL_CL_EVENT_HANDLE 0x309C
#define EGL_COLORSPACE 0x3087
#define EGL_COLORSPACE_LINEAR 0x308A
#define EGL_COLORSPACE_sRGB 0x3089
#define EGL_COLOR_BUFFER_TYPE 0x303F
#define EGL_CONDITION_SATISFIED 0x30F6
#define EGL_CONFIG_CAVEAT 0x3027
#define EGL_CONFIG_ID 0x3028
#define EGL_CONFORMANT 0x3042
#define EGL_CONTEXT_CLIENT_TYPE 0x3097
#define EGL_CONTEXT_CLIENT_VERSION 0x3098
#define EGL_CONTEXT_LOST 0x300E
#define EGL_CONTEXT_MAJOR_VERSION 0x3098
#define EGL_CONTEXT_MINOR_VERSION 0x30FB
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#define EGL_CONTEXT_OPENGL_DEBUG 0x31B0
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#define EGL_CONTEXT_OPENGL_PROFILE_MASK 0x30FD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS 0x31B2
#define EGL_CORE_NATIVE_ENGINE 0x305B
#define EGL_DEFAULT_DISPLAY EGL_CAST(EGLNativeDisplayType,0)
#define EGL_DEPTH_SIZE 0x3025
#define EGL_DEVICE_EXT 0x322C
#define EGL_DISPLAY_SCALING 10000
#define EGL_DMA_BUF_PLANE0_FD_EXT 0x3272
#define EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#define EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#define EGL_DMA_BUF_PLANE0_OFFSET_EXT 0x3273
#define EGL_DMA_BUF_PLANE0_PITCH_EXT 0x3274
#define EGL_DMA_BUF_PLANE1_FD_EXT 0x3275
#define EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#define EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#define EGL_DMA_BUF_PLANE1_OFFSET_EXT 0x3276
#define EGL_DMA_BUF_PLANE1_PITCH_EXT 0x3277
#define EGL_DMA_BUF_PLANE2_FD_EXT 0x3278
#define EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#define EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#define EGL_DMA_BUF_PLANE2_OFFSET_EXT 0x3279
#define EGL_DMA_BUF_PLANE2_PITCH_EXT 0x327A
#define EGL_DMA_BUF_PLANE3_FD_EXT 0x3440
#define EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
#define EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#define EGL_DMA_BUF_PLANE3_OFFSET_EXT 0x3441
#define EGL_DMA_BUF_PLANE3_PITCH_EXT 0x3442
#define EGL_DONT_CARE EGL_CAST(EGLint,-1)
#define EGL_DRAW 0x3059
#define EGL_DRM_DEVICE_FILE_EXT 0x3233
#define EGL_DRM_MASTER_FD_EXT 0x333C
#define EGL_EXTENSIONS 0x3055
#define EGL_FALSE 0
#define EGL_FOREVER 0xFFFFFFFFFFFFFFFF
#define EGL_GL_COLORSPACE 0x309D
#define EGL_GL_COLORSPACE_LINEAR 0x308A
#define EGL_GL_COLORSPACE_SRGB 0x3089
#define EGL_GL_RENDERBUFFER 0x30B9
#define EGL_GL_TEXTURE_2D 0x30B1
#define EGL_GL_TEXTURE_3D 0x30B2
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#define EGL_GL_TEXTURE_LEVEL 0x30BC
#define EGL_GL_TEXTURE_ZOFFSET 0x30BD
#define EGL_GREEN_SIZE 0x3023
#define EGL_HEIGHT 0x3056
#define EGL_HORIZONTAL_RESOLUTION 0x3090
#define EGL_IMAGE_PRESERVED 0x30D2
#define EGL_ITU_REC2020_EXT 0x3281
#define EGL_ITU_REC601_EXT 0x327F
#define EGL_ITU_REC709_EXT 0x3280
#define EGL_LARGEST_PBUFFER 0x3058
#define EGL_LEVEL 0x3029
#define EGL_LINUX_DMA_BUF_EXT 0x3270
#define EGL_LINUX_DRM_FOURCC_EXT 0x3271
#define EGL_LOSE_CONTEXT_ON_RESET 0x31BF
#define EGL_LUMINANCE_BUFFER 0x308F
#define EGL_LUMINANCE_SIZE 0x303D
#define EGL_MATCH_NATIVE_PIXMAP 0x3041
#define EGL_MAX_PBUFFER_HEIGHT 0x302A
#define EGL_MAX_PBUFFER_PIXELS 0x302B
#define EGL_MAX_PBUFFER_WIDTH 0x302C
#define EGL_MAX_SWAP_INTERVAL 0x303C
#define EGL_MIN_SWAP_INTERVAL 0x303B
#define EGL_MIPMAP_LEVEL 0x3083
#define EGL_MIPMAP_TEXTURE 0x3082
#define EGL_MULTISAMPLE_RESOLVE 0x3099
#define EGL_MULTISAMPLE_RESOLVE_BOX 0x309B
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A
#define EGL_NATIVE_RENDERABLE 0x302D
#define EGL_NATIVE_VISUAL_ID 0x302E
#define EGL_NATIVE_VISUAL_TYPE 0x302F
#define EGL_NONE 0x3038
#define EGL_NON_CONFORMANT_CONFIG 0x3051
#define EGL_NOT_INITIALIZED 0x3001
#define EGL_NO_CONTEXT EGL_CAST(EGLContext,0)
#define EGL_NO_DEVICE_EXT EGL_CAST(EGLDeviceEXT,0)
#define EGL_NO_DISPLAY EGL_CAST(EGLDisplay,0)
#define EGL_NO_IMAGE EGL_CAST(EGLImage,0)
#define EGL_NO_RESET_NOTIFICATION 0x31BE
#define EGL_NO_SURFACE EGL_CAST(EGLSurface,0)
#define EGL_NO_SYNC EGL_CAST(EGLSync,0)
#define EGL_NO_TEXTURE 0x305C
#define EGL_OPENGL_API 0x30A2
#define EGL_OPENGL_BIT 0x0008
#define EGL_OPENGL_ES2_BIT 0x0004
#define EGL_OPENGL_ES3_BIT 0x00000040
#define EGL_OPENGL_ES_API 0x30A0
#define EGL_OPENGL_ES_BIT 0x0001
#define EGL_OPENVG_API 0x30A1
#define EGL_OPENVG_BIT 0x0002
#define EGL_OPENVG_IMAGE 0x3096
#define EGL_PBUFFER_BIT 0x0001
#define EGL_PIXEL_ASPECT_RATIO 0x3092
#define EGL_PIXMAP_BIT 0x0002
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#define EGL_READ 0x305A
#define EGL_RED_SIZE 0x3024
#define EGL_RENDERABLE_TYPE 0x3040
#define EGL_RENDER_BUFFER 0x3086
#define EGL_RGB_BUFFER 0x308E
#define EGL_SAMPLES 0x3031
#define EGL_SAMPLE_BUFFERS 0x3032
#define EGL_SAMPLE_RANGE_HINT_EXT 0x327C
#define EGL_SIGNALED 0x30F2
#define EGL_SINGLE_BUFFER 0x3085
#define EGL_SLOW_CONFIG 0x3050
#define EGL_STENCIL_SIZE 0x3026
#define EGL_SUCCESS 0x3000
#define EGL_SURFACE_TYPE 0x3033
#define EGL_SWAP_BEHAVIOR 0x3093
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400
#define EGL_SYNC_CL_EVENT 0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE 0x30FF
#define EGL_SYNC_CONDITION 0x30F8
#define EGL_SYNC_FENCE 0x30F9
#define EGL_SYNC_FLUSH_COMMANDS_BIT 0x0001
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE 0x30F0
#define EGL_SYNC_STATUS 0x30F1
#define EGL_SYNC_TYPE 0x30F7
#define EGL_TEXTURE_2D 0x305F
#define EGL_TEXTURE_FORMAT 0x3080
#define EGL_TEXTURE_RGB 0x305D
#define EGL_TEXTURE_RGBA 0x305E
#define EGL_TEXTURE_TARGET 0x3081
#define EGL_TIMEOUT_EXPIRED 0x30F5
#define EGL_TRANSPARENT_BLUE_VALUE 0x3035
#define EGL_TRANSPARENT_GREEN_VALUE 0x3036
#define EGL_TRANSPARENT_RED_VALUE 0x3037
#define EGL_TRANSPARENT_RGB 0x3052
#define EGL_TRANSPARENT_TYPE 0x3034
#define EGL_TRUE 1
#define EGL_UNKNOWN EGL_CAST(EGLint,-1)
#define EGL_UNSIGNALED 0x30F3
#define EGL_VENDOR 0x3053
#define EGL_VERSION 0x3054
#define EGL_VERTICAL_RESOLUTION 0x3091
#define EGL_VG_ALPHA_FORMAT 0x3088
#define EGL_VG_ALPHA_FORMAT_NONPRE 0x308B
#define EGL_VG_ALPHA_FORMAT_PRE 0x308C
#define EGL_VG_ALPHA_FORMAT_PRE_BIT 0x0040
#define EGL_VG_COLORSPACE 0x3087
#define EGL_VG_COLORSPACE_LINEAR 0x308A
#define EGL_VG_COLORSPACE_LINEAR_BIT 0x0020
#define EGL_VG_COLORSPACE_sRGB 0x3089
#define EGL_WIDTH 0x3057
#define EGL_WINDOW_BIT 0x0004
#define EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#define EGL_YUV_CHROMA_SITING_0_5_EXT 0x3285
#define EGL_YUV_CHROMA_SITING_0_EXT 0x3284
#define EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#define EGL_YUV_COLOR_SPACE_HINT_EXT 0x327B
#define EGL_YUV_FULL_RANGE_EXT 0x3282
#define EGL_YUV_NARROW_RANGE_EXT 0x3283


#include <KHR/khrplatform.h>
#include <EGL/eglplatform.h>











struct AHardwareBuffer;
struct wl_buffer;
struct wl_display;
struct wl_resource;

typedef unsigned int EGLBoolean;
typedef unsigned int EGLenum;
typedef intptr_t EGLAttribKHR;
typedef intptr_t EGLAttrib;
typedef void *EGLClientBuffer;
typedef void *EGLConfig;
typedef void *EGLContext;
typedef void *EGLDeviceEXT;
typedef void *EGLDisplay;
typedef void *EGLImage;
typedef void *EGLImageKHR;
typedef void *EGLLabelKHR;
typedef void *EGLObjectKHR;
typedef void *EGLOutputLayerEXT;
typedef void *EGLOutputPortEXT;
typedef void *EGLStreamKHR;
typedef void *EGLSurface;
typedef void *EGLSync;
typedef void *EGLSyncKHR;
typedef void *EGLSyncNV;
typedef void (*__eglMustCastToProperFunctionPointerType)(void);
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef khronos_utime_nanoseconds_t EGLTimeNV;
typedef khronos_utime_nanoseconds_t EGLuint64NV;
typedef khronos_uint64_t EGLuint64KHR;
typedef khronos_stime_nanoseconds_t EGLnsecsANDROID;
typedef int EGLNativeFileDescriptorKHR;
typedef khronos_ssize_t EGLsizeiANDROID;
typedef void (*EGLSetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, const void *value, EGLsizeiANDROID valueSize);
typedef EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, void *value, EGLsizeiANDROID valueSize);
struct EGLClientPixmapHI {
    void  *pData;
    EGLint iWidth;
    EGLint iHeight;
    EGLint iStride;
};
typedef void (GLAD_API_PTR *EGLDEBUGPROCKHR)(EGLenum error,const char *command,EGLint messageType,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,const char* message);
#define PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#define PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#define PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
#define PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC


#define EGL_VERSION_1_0 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_0;
#define EGL_VERSION_1_1 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_1;
#define EGL_VERSION_1_2 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_2;
#define EGL_VERSION_1_3 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_3;
#define EGL_VERSION_1_4 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_4;
#define EGL_VERSION_1_5 1
GLAD_API_CALL int GLAD_EGL_VERSION_1_5;
#define EGL_EXT_device_drm 1
GLAD_API_CALL int GLAD_EGL_EXT_device_drm;
#define EGL_EXT_device_enumeration 1
GLAD_API_CALL int GLAD_EGL_EXT_device_enumeration;
#define EGL_EXT_device_query 1
GLAD_API_CALL int GLAD_EGL_EXT_device_query;
#define EGL_EXT_image_dma_buf_import 1
GLAD_API_CALL int GLAD_EGL_EXT_image_dma_buf_import;
#define EGL_EXT_image_dma_buf_import_modifiers 1
GLAD_API_CALL int GLAD_EGL_EXT_image_dma_buf_import_modifiers;
#define EGL_EXT_platform_device 1
GLAD_API_CALL int GLAD_EGL_EXT_platform_device;
#define EGL_MESA_image_dma_buf_export 1
GLAD_API_CALL int GLAD_EGL_MESA_image_dma_buf_export;
#define EGL_MESA_query_driver 1
GLAD_API_CALL int GLAD_EGL_MESA_query_driver;


typedef EGLBoolean (GLAD_API_PTR *PFNEGLBINDAPIPROC)(EGLenum api);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLBINDTEXIMAGEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLCHOOSECONFIGPROC)(EGLDisplay dpy, const EGLint * attrib_list, EGLConfig * configs, EGLint config_size, EGLint * num_config);
typedef EGLint (GLAD_API_PTR *PFNEGLCLIENTWAITSYNCPROC)(EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLCOPYBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLContext (GLAD_API_PTR *PFNEGLCREATECONTEXTPROC)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint * attrib_list);
typedef EGLImage (GLAD_API_PTR *PFNEGLCREATEIMAGEPROC)(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC)(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEPBUFFERSURFACEPROC)(EGLDisplay dpy, EGLConfig config, const EGLint * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEPIXMAPSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC)(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLAttrib * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEPLATFORMWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLAttrib * attrib_list);
typedef EGLSync (GLAD_API_PTR *PFNEGLCREATESYNCPROC)(EGLDisplay dpy, EGLenum type, const EGLAttrib * attrib_list);
typedef EGLSurface (GLAD_API_PTR *PFNEGLCREATEWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint * attrib_list);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLDESTROYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLDESTROYIMAGEPROC)(EGLDisplay dpy, EGLImage image);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLDESTROYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLDESTROYSYNCPROC)(EGLDisplay dpy, EGLSync sync);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLEXPORTDMABUFIMAGEMESAPROC)(EGLDisplay dpy, EGLImageKHR image, int * fds, EGLint * strides, EGLint * offsets);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)(EGLDisplay dpy, EGLImageKHR image, int * fourcc, int * num_planes, EGLuint64KHR * modifiers);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLGETCONFIGATTRIBPROC)(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLGETCONFIGSPROC)(EGLDisplay dpy, EGLConfig * configs, EGLint config_size, EGLint * num_config);
typedef EGLContext (GLAD_API_PTR *PFNEGLGETCURRENTCONTEXTPROC)(void);
typedef EGLDisplay (GLAD_API_PTR *PFNEGLGETCURRENTDISPLAYPROC)(void);
typedef EGLSurface (GLAD_API_PTR *PFNEGLGETCURRENTSURFACEPROC)(EGLint readdraw);
typedef EGLDisplay (GLAD_API_PTR *PFNEGLGETDISPLAYPROC)(EGLNativeDisplayType display_id);
typedef char * (GLAD_API_PTR *PFNEGLGETDISPLAYDRIVERCONFIGPROC)(EGLDisplay dpy);
typedef const char * (GLAD_API_PTR *PFNEGLGETDISPLAYDRIVERNAMEPROC)(EGLDisplay dpy);
typedef EGLint (GLAD_API_PTR *PFNEGLGETERRORPROC)(void);
typedef EGLDisplay (GLAD_API_PTR *PFNEGLGETPLATFORMDISPLAYPROC)(EGLenum platform, void * native_display, const EGLAttrib * attrib_list);
typedef __eglMustCastToProperFunctionPointerType (GLAD_API_PTR *PFNEGLGETPROCADDRESSPROC)(const char * procname);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLGETSYNCATTRIBPROC)(EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLINITIALIZEPROC)(EGLDisplay dpy, EGLint * major, EGLint * minor);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLMAKECURRENTPROC)(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLenum (GLAD_API_PTR *PFNEGLQUERYAPIPROC)(void);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYDEVICEATTRIBEXTPROC)(EGLDeviceEXT device, EGLint attribute, EGLAttrib * value);
typedef const char * (GLAD_API_PTR *PFNEGLQUERYDEVICESTRINGEXTPROC)(EGLDeviceEXT device, EGLint name);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYDEVICESEXTPROC)(EGLint max_devices, EGLDeviceEXT * devices, EGLint * num_devices);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYDISPLAYATTRIBEXTPROC)(EGLDisplay dpy, EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYDMABUFFORMATSEXTPROC)(EGLDisplay dpy, EGLint max_formats, EGLint * formats, EGLint * num_formats);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYDMABUFMODIFIERSEXTPROC)(EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR * modifiers, EGLBoolean * external_only, EGLint * num_modifiers);
typedef const char * (GLAD_API_PTR *PFNEGLQUERYSTRINGPROC)(EGLDisplay dpy, EGLint name);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLQUERYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLRELEASETEXIMAGEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLRELEASETHREADPROC)(void);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLSURFACEATTRIBPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLSWAPBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLSWAPINTERVALPROC)(EGLDisplay dpy, EGLint interval);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLTERMINATEPROC)(EGLDisplay dpy);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLWAITCLIENTPROC)(void);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLWAITGLPROC)(void);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLWAITNATIVEPROC)(EGLint engine);
typedef EGLBoolean (GLAD_API_PTR *PFNEGLWAITSYNCPROC)(EGLDisplay dpy, EGLSync sync, EGLint flags);

GLAD_API_CALL PFNEGLBINDAPIPROC glad_eglBindAPI;
#define eglBindAPI glad_eglBindAPI
GLAD_API_CALL PFNEGLBINDTEXIMAGEPROC glad_eglBindTexImage;
#define eglBindTexImage glad_eglBindTexImage
GLAD_API_CALL PFNEGLCHOOSECONFIGPROC glad_eglChooseConfig;
#define eglChooseConfig glad_eglChooseConfig
GLAD_API_CALL PFNEGLCLIENTWAITSYNCPROC glad_eglClientWaitSync;
#define eglClientWaitSync glad_eglClientWaitSync
GLAD_API_CALL PFNEGLCOPYBUFFERSPROC glad_eglCopyBuffers;
#define eglCopyBuffers glad_eglCopyBuffers
GLAD_API_CALL PFNEGLCREATECONTEXTPROC glad_eglCreateContext;
#define eglCreateContext glad_eglCreateContext
GLAD_API_CALL PFNEGLCREATEIMAGEPROC glad_eglCreateImage;
#define eglCreateImage glad_eglCreateImage
GLAD_API_CALL PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC glad_eglCreatePbufferFromClientBuffer;
#define eglCreatePbufferFromClientBuffer glad_eglCreatePbufferFromClientBuffer
GLAD_API_CALL PFNEGLCREATEPBUFFERSURFACEPROC glad_eglCreatePbufferSurface;
#define eglCreatePbufferSurface glad_eglCreatePbufferSurface
GLAD_API_CALL PFNEGLCREATEPIXMAPSURFACEPROC glad_eglCreatePixmapSurface;
#define eglCreatePixmapSurface glad_eglCreatePixmapSurface
GLAD_API_CALL PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC glad_eglCreatePlatformPixmapSurface;
#define eglCreatePlatformPixmapSurface glad_eglCreatePlatformPixmapSurface
GLAD_API_CALL PFNEGLCREATEPLATFORMWINDOWSURFACEPROC glad_eglCreatePlatformWindowSurface;
#define eglCreatePlatformWindowSurface glad_eglCreatePlatformWindowSurface
GLAD_API_CALL PFNEGLCREATESYNCPROC glad_eglCreateSync;
#define eglCreateSync glad_eglCreateSync
GLAD_API_CALL PFNEGLCREATEWINDOWSURFACEPROC glad_eglCreateWindowSurface;
#define eglCreateWindowSurface glad_eglCreateWindowSurface
GLAD_API_CALL PFNEGLDESTROYCONTEXTPROC glad_eglDestroyContext;
#define eglDestroyContext glad_eglDestroyContext
GLAD_API_CALL PFNEGLDESTROYIMAGEPROC glad_eglDestroyImage;
#define eglDestroyImage glad_eglDestroyImage
GLAD_API_CALL PFNEGLDESTROYSURFACEPROC glad_eglDestroySurface;
#define eglDestroySurface glad_eglDestroySurface
GLAD_API_CALL PFNEGLDESTROYSYNCPROC glad_eglDestroySync;
#define eglDestroySync glad_eglDestroySync
GLAD_API_CALL PFNEGLEXPORTDMABUFIMAGEMESAPROC glad_eglExportDMABUFImageMESA;
#define eglExportDMABUFImageMESA glad_eglExportDMABUFImageMESA
GLAD_API_CALL PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC glad_eglExportDMABUFImageQueryMESA;
#define eglExportDMABUFImageQueryMESA glad_eglExportDMABUFImageQueryMESA
GLAD_API_CALL PFNEGLGETCONFIGATTRIBPROC glad_eglGetConfigAttrib;
#define eglGetConfigAttrib glad_eglGetConfigAttrib
GLAD_API_CALL PFNEGLGETCONFIGSPROC glad_eglGetConfigs;
#define eglGetConfigs glad_eglGetConfigs
GLAD_API_CALL PFNEGLGETCURRENTCONTEXTPROC glad_eglGetCurrentContext;
#define eglGetCurrentContext glad_eglGetCurrentContext
GLAD_API_CALL PFNEGLGETCURRENTDISPLAYPROC glad_eglGetCurrentDisplay;
#define eglGetCurrentDisplay glad_eglGetCurrentDisplay
GLAD_API_CALL PFNEGLGETCURRENTSURFACEPROC glad_eglGetCurrentSurface;
#define eglGetCurrentSurface glad_eglGetCurrentSurface
GLAD_API_CALL PFNEGLGETDISPLAYPROC glad_eglGetDisplay;
#define eglGetDisplay glad_eglGetDisplay
GLAD_API_CALL PFNEGLGETDISPLAYDRIVERCONFIGPROC glad_eglGetDisplayDriverConfig;
#define eglGetDisplayDriverConfig glad_eglGetDisplayDriverConfig
GLAD_API_CALL PFNEGLGETDISPLAYDRIVERNAMEPROC glad_eglGetDisplayDriverName;
#define eglGetDisplayDriverName glad_eglGetDisplayDriverName
GLAD_API_CALL PFNEGLGETERRORPROC glad_eglGetError;
#define eglGetError glad_eglGetError
GLAD_API_CALL PFNEGLGETPLATFORMDISPLAYPROC glad_eglGetPlatformDisplay;
#define eglGetPlatformDisplay glad_eglGetPlatformDisplay
GLAD_API_CALL PFNEGLGETPROCADDRESSPROC glad_eglGetProcAddress;
#define eglGetProcAddress glad_eglGetProcAddress
GLAD_API_CALL PFNEGLGETSYNCATTRIBPROC glad_eglGetSyncAttrib;
#define eglGetSyncAttrib glad_eglGetSyncAttrib
GLAD_API_CALL PFNEGLINITIALIZEPROC glad_eglInitialize;
#define eglInitialize glad_eglInitialize
GLAD_API_CALL PFNEGLMAKECURRENTPROC glad_eglMakeCurrent;
#define eglMakeCurrent glad_eglMakeCurrent
GLAD_API_CALL PFNEGLQUERYAPIPROC glad_eglQueryAPI;
#define eglQueryAPI glad_eglQueryAPI
GLAD_API_CALL PFNEGLQUERYCONTEXTPROC glad_eglQueryContext;
#define eglQueryContext glad_eglQueryContext
GLAD_API_CALL PFNEGLQUERYDEVICEATTRIBEXTPROC glad_eglQueryDeviceAttribEXT;
#define eglQueryDeviceAttribEXT glad_eglQueryDeviceAttribEXT
GLAD_API_CALL PFNEGLQUERYDEVICESTRINGEXTPROC glad_eglQueryDeviceStringEXT;
#define eglQueryDeviceStringEXT glad_eglQueryDeviceStringEXT
GLAD_API_CALL PFNEGLQUERYDEVICESEXTPROC glad_eglQueryDevicesEXT;
#define eglQueryDevicesEXT glad_eglQueryDevicesEXT
GLAD_API_CALL PFNEGLQUERYDISPLAYATTRIBEXTPROC glad_eglQueryDisplayAttribEXT;
#define eglQueryDisplayAttribEXT glad_eglQueryDisplayAttribEXT
GLAD_API_CALL PFNEGLQUERYDMABUFFORMATSEXTPROC glad_eglQueryDmaBufFormatsEXT;
#define eglQueryDmaBufFormatsEXT glad_eglQueryDmaBufFormatsEXT
GLAD_API_CALL PFNEGLQUERYDMABUFMODIFIERSEXTPROC glad_eglQueryDmaBufModifiersEXT;
#define eglQueryDmaBufModifiersEXT glad_eglQueryDmaBufModifiersEXT
GLAD_API_CALL PFNEGLQUERYSTRINGPROC glad_eglQueryString;
#define eglQueryString glad_eglQueryString
GLAD_API_CALL PFNEGLQUERYSURFACEPROC glad_eglQuerySurface;
#define eglQuerySurface glad_eglQuerySurface
GLAD_API_CALL PFNEGLRELEASETEXIMAGEPROC glad_eglReleaseTexImage;
#define eglReleaseTexImage glad_eglReleaseTexImage
GLAD_API_CALL PFNEGLRELEASETHREADPROC glad_eglReleaseThread;
#define eglReleaseThread glad_eglReleaseThread
GLAD_API_CALL PFNEGLSURFACEATTRIBPROC glad_eglSurfaceAttrib;
#define eglSurfaceAttrib glad_eglSurfaceAttrib
GLAD_API_CALL PFNEGLSWAPBUFFERSPROC glad_eglSwapBuffers;
#define eglSwapBuffers glad_eglSwapBuffers
GLAD_API_CALL PFNEGLSWAPINTERVALPROC glad_eglSwapInterval;
#define eglSwapInterval glad_eglSwapInterval
GLAD_API_CALL PFNEGLTERMINATEPROC glad_eglTerminate;
#define eglTerminate glad_eglTerminate
GLAD_API_CALL PFNEGLWAITCLIENTPROC glad_eglWaitClient;
#define eglWaitClient glad_eglWaitClient
GLAD_API_CALL PFNEGLWAITGLPROC glad_eglWaitGL;
#define eglWaitGL glad_eglWaitGL
GLAD_API_CALL PFNEGLWAITNATIVEPROC glad_eglWaitNative;
#define eglWaitNative glad_eglWaitNative
GLAD_API_CALL PFNEGLWAITSYNCPROC glad_eglWaitSync;
#define eglWaitSync glad_eglWaitSync





GLAD_API_CALL int gladLoadEGLUserPtr(EGLDisplay display, GLADuserptrloadfunc load, void *userptr);
GLAD_API_CALL int gladLoadEGL(EGLDisplay display, GLADloadfunc load);


#ifdef __cplusplus
}
#endif
#endif
