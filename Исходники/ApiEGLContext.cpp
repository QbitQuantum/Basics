void ApiChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config, EGLBoolean ret)
{
    stEglDisplay    *display    = _GetDisplay(dpy);
    const EGLint    *value      = attrib_list;
    stEglConfig     *p          = NULL;
    EGLBoolean      bFinish     = EGL_FALSE;
    EGLint          num         = num_config ? *num_config : 0;

    if (configs == NULL)
    {
        return;
    }

    for (GLint i=0; i<num; i++)
    {
        p = new stEglConfig();

        if (p)
        {
            p->config = configs[i];
            _ParseAttrbutes(dpy, value, p);
        }
        else
        {
            Abort("%s(%d)\n", __FUNCTION__, __LINE__);
            return;
        }

        if (display->eglConfStack)
        {
            stEglConfig *pTmp = display->eglConfStack;
            display->eglConfStack = p;
            p->next = pTmp;
        }
        else
        {
            display->eglConfStack = p;
        }
    }

    CTX_ANALYZER_FUNC6(ChooseConfig, EGLOutput, EGL_OUT_BUF_SIZE, dpy, attrib_list, configs, config_size, num_config, ret);
}