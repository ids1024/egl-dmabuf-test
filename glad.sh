#!/bin/bash

if [ ! -d glad ]; then
	git clone https://github.com/Dav1dde/glad
fi

PYTHONPATH=$PWD/glad python -m glad \
	--api egl=1.5,gles2=2.0 \
	--extensions EGL_EXT_image_dma_buf_import,EGL_MESA_image_dma_buf_export,EGL_EXT_platform_device,EGL_EXT_device_query,EGL_MESA_query_driver,EGL_EXT_device_enumeration,GL_OES_EGL_image,GL_OES_EGL_image_external,EGL_EXT_image_dma_buf_import_modifiers,EGL_EXT_device_drm,EGL_KHR_surfaceless_context,GL_OES_rgb8_rgba8,EGL_MESA_platform_gbm \
	--out-path .
