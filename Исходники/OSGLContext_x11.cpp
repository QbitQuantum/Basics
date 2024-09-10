void
OSGLContext_x11::initGLXData(OSGLContext_glx_data* glxInfo)
{
    //Sets all bits to 0
    memset( glxInfo->_imp.get(), 0, sizeof(OSGLContext_glx_dataPrivate) );

    XInitThreads();
    glxInfo->_imp->x11.display = XOpenDisplay(NULL);
    if (!glxInfo->_imp->x11.display) {
        throw std::runtime_error("X11: Failed to open display");
    }
    glxInfo->_imp->x11.screen = DefaultScreen(glxInfo->_imp->x11.display);
    glxInfo->_imp->x11.root = RootWindow(glxInfo->_imp->x11.display, glxInfo->_imp->x11.screen);
    glxInfo->_imp->x11.context = XUniqueContext();


    const char* sonames[] =
    {
#if defined(__CYGWIN__)
        "libGL-1.so",
#else
        "libGL.so.1",
        "libGL.so",
#endif
        NULL
    };

    for (int i = 0; sonames[i]; ++i) {
        glxInfo->_imp->handle = dlopen(sonames[i], RTLD_LAZY | RTLD_GLOBAL);
        if (glxInfo->_imp->handle) {
            break;
        }
    }

    if (!glxInfo->_imp->handle) {
        throw std::runtime_error("GLX: Failed to load GLX");
    }

    glxInfo->_imp->GetFBConfigs = (PFNGLXGETFBCONFIGSPROC)dlsym(glxInfo->_imp->handle, "glXGetFBConfigs");
    glxInfo->_imp->GetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)dlsym(glxInfo->_imp->handle, "glXGetFBConfigAttrib");
    glxInfo->_imp->GetClientString = (PFNGLXGETCLIENTSTRINGPROC)dlsym(glxInfo->_imp->handle, "glXGetClientString");
    glxInfo->_imp->QueryExtension = (PFNGLXQUERYEXTENSIONPROC)dlsym(glxInfo->_imp->handle, "glXQueryExtension");
    glxInfo->_imp->QueryVersion = (PFNGLXQUERYVERSIONPROC)dlsym(glxInfo->_imp->handle, "glXQueryVersion");
    glxInfo->_imp->DestroyContext = (PFNGLXDESTROYCONTEXTPROC)dlsym(glxInfo->_imp->handle, "glXDestroyContext");
    glxInfo->_imp->MakeCurrent = (PFNGLXMAKECURRENTPROC)dlsym(glxInfo->_imp->handle, "glXMakeCurrent");
    glxInfo->_imp->SwapBuffers = (PFNGLXSWAPBUFFERSPROC)dlsym(glxInfo->_imp->handle, "glXSwapBuffers");
    glxInfo->_imp->QueryExtensionsString = (PFNGLXQUERYEXTENSIONSSTRINGPROC)dlsym(glxInfo->_imp->handle, "glXQueryExtensionsString");
    glxInfo->_imp->CreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)dlsym(glxInfo->_imp->handle, "glXCreateNewContext");
    glxInfo->_imp->CreateWindow = (PFNGLXCREATEWINDOWPROC)dlsym(glxInfo->_imp->handle, "glXCreateWindow");
    glxInfo->_imp->DestroyWindow = (PFNGLXDESTROYWINDOWPROC)dlsym(glxInfo->_imp->handle, "glXDestroyWindow");
    glxInfo->_imp->GetProcAddress = (PFNGLXGETPROCADDRESSPROC)dlsym(glxInfo->_imp->handle, "glXGetProcAddress");
    glxInfo->_imp->GetProcAddressARB = (PFNGLXGETPROCADDRESSPROC)dlsym(glxInfo->_imp->handle, "glXGetProcAddressARB");
    glxInfo->_imp->GetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)dlsym(glxInfo->_imp->handle, "glXGetVisualFromFBConfig");
    glxInfo->_imp->MakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC)dlsym(glxInfo->_imp->handle, "glXMakeContextCurrent");
    glxInfo->_imp->IsDirect = (PFNGLXISDIRECT)dlsym(glxInfo->_imp->handle, "glXIsDirect");

    if ( !glxInfo->_imp->QueryExtension(glxInfo->_imp->x11.display, &glxInfo->_imp->errorBase, &glxInfo->_imp->eventBase) ) {
        throw std::runtime_error("GLX: GLX extension not found");
    }

    if ( !glxInfo->_imp->QueryVersion(glxInfo->_imp->x11.display, &glxInfo->_imp->major, &glxInfo->_imp->minor) ) {
        throw std::runtime_error("GLX: Failed to query GLX version");
    }

    if ( (glxInfo->_imp->major == 1) && (glxInfo->_imp->minor < 3) ) {
        throw std::runtime_error("GLX: GLX version 1.3 is required");
    }

    if ( extensionSupported(glxInfo, "GLX_EXT_swap_control") ) {
        glxInfo->_imp->SwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)getProcAddress(glxInfo, "glXSwapIntervalEXT");
        if (glxInfo->_imp->SwapIntervalEXT) {
            glxInfo->_imp->EXT_swap_control = GL_TRUE;
        }
    }

    if ( extensionSupported(glxInfo, "GLX_SGI_swap_control") ) {
        glxInfo->_imp->SwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)getProcAddress(glxInfo, "glXSwapIntervalSGI");

        if (glxInfo->_imp->SwapIntervalSGI) {
            glxInfo->_imp->SGI_swap_control = GL_TRUE;
        }
    }

    if ( extensionSupported(glxInfo, "GLX_MESA_swap_control") ) {
        glxInfo->_imp->SwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)getProcAddress(glxInfo, "glXSwapIntervalMESA");

        if (glxInfo->_imp->SwapIntervalMESA) {
            glxInfo->_imp->MESA_swap_control = GL_TRUE;
        }
    }

    if ( extensionSupported(glxInfo, "GLX_MESA_query_renderer") ) {
        glxInfo->_imp->QueryRendererIntegerMESA = (PFNGLXQUERYRENDERERINTEGERMESA)getProcAddress(glxInfo, "glXQueryRendererIntegerMESA");
        glxInfo->_imp->QueryCurrentRendererIntegerMESA = (PFNGLXQUERYCURRENTRENDERERINTEGERMESA)getProcAddress(glxInfo, "glXQueryCurrentRendererIntegerMESA");
        glxInfo->_imp->QueryRendererStringMesa = (PFNGLXQUERYRENDERERSTRINGMESA)getProcAddress(glxInfo, "glXQueryRendererStringMESA");
        glxInfo->_imp->QueryCurrentRendererStringMesa = (PFNGLXQUERYCURRENTRENDERERSTRINGMESA)getProcAddress(glxInfo, "glXQueryCurrentRendererStringMESA");
        if (glxInfo->_imp->QueryRendererIntegerMESA) {
            glxInfo->_imp->MESA_query_renderer = GL_TRUE;
        }
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_multisample") ) {
        glxInfo->_imp->ARB_multisample = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_framebuffer_sRGB") ) {
        glxInfo->_imp->ARB_framebuffer_sRGB = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_EXT_framebuffer_sRGB") ) {
        glxInfo->_imp->EXT_framebuffer_sRGB = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_create_context") ) {
        glxInfo->_imp->CreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)getProcAddress(glxInfo, "glXCreateContextAttribsARB");

        if (glxInfo->_imp->CreateContextAttribsARB) {
            glxInfo->_imp->ARB_create_context = GL_TRUE;
        }
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_create_context_robustness") ) {
        glxInfo->_imp->ARB_create_context_robustness = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_create_context_profile") ) {
        glxInfo->_imp->ARB_create_context_profile = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_EXT_create_context_es2_profile") ) {
        glxInfo->_imp->EXT_create_context_es2_profile = GL_TRUE;
    }

    if ( extensionSupported(glxInfo, "GLX_ARB_context_flush_control") ) {
        glxInfo->_imp->ARB_context_flush_control = GL_TRUE;
    }
} // initGLXData