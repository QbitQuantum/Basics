EGLBoolean EGLAPIENTRY DestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    EVENT("(EGLDisplay dpy = 0x%0.8p, EGLContext ctx = 0x%0.8p)", dpy, ctx);
    Thread *thread = GetCurrentThread();

    Display *display     = static_cast<Display *>(dpy);
    gl::Context *context = static_cast<gl::Context *>(ctx);

    Error error = ValidateContext(display, context);
    if (error.isError())
    {
        thread->setError(error);
        return EGL_FALSE;
    }

    if (ctx == EGL_NO_CONTEXT)
    {
        thread->setError(EglBadContext());
        return EGL_FALSE;
    }

    if (context == thread->getContext())
    {
        thread->setCurrent(nullptr);
    }

    error = display->destroyContext(context);
    if (error.isError())
    {
        thread->setError(error);
        return EGL_FALSE;
    }

    thread->setError(NoError());
    return EGL_TRUE;
}