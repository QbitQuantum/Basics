OSGLContext_win::OSGLContext_win(const FramebufferConfig& pixelFormatAttrs,
                                 int major,
                                 int minor,
                                 bool coreProfile,
                                 const GLRendererID &rendererID,
                                 const OSGLContext_win* shareContext)
    : _dc(0)
    , _handle(0)
    , _interval(0)
    , _windowHandle(0)
{
    if ( !createWindow(&_windowHandle) ) {
        throw std::runtime_error("WGL: Failed to create window");
    }

    createGLContext(pixelFormatAttrs, major, minor, coreProfile, rendererID, shareContext);

    if ( analyzeContextWGL(pixelFormatAttrs, major, minor) ) {
        // Some window hints require us to re-create the context using WGL
        // extensions retrieved through the current context, as we cannot
        // check for WGL extensions or retrieve WGL entry points before we
        // have a current context (actually until we have implicitly loaded
        // the vendor ICD)

        // Yes, this is strange, and yes, this is the proper way on WGL

        // As Windows only allows you to set the pixel format once for
        // a window, we need to destroy the current window and create a new
        // one to be able to use the new pixel format

        // Technically, it may be possible to keep the old window around if
        // we're just creating an OpenGL 3.0+ context with the same pixel
        // format, but it's not worth the added code complexity

        // First we clear the current context (the one we just created)
        // This is usually done by glfwDestroyWindow, but as we're not doing
        // full GLFW window destruction, it's duplicated here
        makeContextCurrent(NULL);

        // Next destroy the Win32 window and WGL context (without resetting
        // or destroying the GLFW window object)
        destroyContext();
        destroyWindow();

        // ...and then create them again, this time with better APIs
        if ( !createWindow(&_windowHandle) ) {
            throw std::runtime_error("WGL: Failed to create window");
        }

        createGLContext(pixelFormatAttrs, major, minor, coreProfile, rendererID, shareContext);
    }
}