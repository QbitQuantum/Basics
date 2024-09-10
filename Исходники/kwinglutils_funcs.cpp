void glxResolveFunctions()
{
    // handle OpenGL extensions functions
    glXGetProcAddress = (glXGetProcAddress_func) getProcAddress("glXGetProcAddress");
    if (glXGetProcAddress == nullptr)
        glXGetProcAddress = (glXGetProcAddress_func) getProcAddress("glXGetProcAddressARB");
    glXQueryDrawable = (glXQueryDrawable_func) getProcAddress("glXQueryDrawable");
    if (hasGLExtension(QStringLiteral("GLX_EXT_texture_from_pixmap"))) {
        glXBindTexImageEXT = (glXBindTexImageEXT_func) getProcAddress("glXBindTexImageEXT");
        glXReleaseTexImageEXT = (glXReleaseTexImageEXT_func) getProcAddress("glXReleaseTexImageEXT");
    } else {
        glXBindTexImageEXT = nullptr;
        glXReleaseTexImageEXT = nullptr;
    }
    if (hasGLExtension(QStringLiteral("GLX_MESA_copy_sub_buffer")))
        glXCopySubBuffer = (glXCopySubBuffer_func) getProcAddress("glXCopySubBufferMESA");
    else
        glXCopySubBuffer = nullptr;
    if (hasGLExtension(QStringLiteral("GLX_SGI_video_sync"))) {
        glXGetVideoSync = (glXGetVideoSync_func) getProcAddress("glXGetVideoSyncSGI");
        glXWaitVideoSync = (glXWaitVideoSync_func) getProcAddress("glXWaitVideoSyncSGI");
    } else {
        glXGetVideoSync = nullptr;
        glXWaitVideoSync = nullptr;
    }

    if (hasGLExtension(QStringLiteral("GLX_SGI_swap_control")))
        glXSwapIntervalSGI = (glXSwapIntervalSGI_func) getProcAddress("glXSwapIntervalSGI");
    else
        glXSwapIntervalSGI = nullptr;
    if (hasGLExtension(QStringLiteral("GLX_EXT_swap_control")))
        glXSwapIntervalEXT = (glXSwapIntervalEXT_func) getProcAddress("glXSwapIntervalEXT");
    else
        glXSwapIntervalEXT = nullptr;
    if (hasGLExtension(QStringLiteral("GLX_MESA_swap_control")))
        glXSwapIntervalMESA = (glXSwapIntervalMESA_func) getProcAddress("glXSwapIntervalMESA");
    else
        glXSwapIntervalMESA = nullptr;

    if (hasGLExtension(QStringLiteral("GLX_ARB_create_context")))
        glXCreateContextAttribsARB = (glXCreateContextAttribsARB_func) getProcAddress("glXCreateContextAttribsARB");
    else
        glXCreateContextAttribsARB = nullptr;
}