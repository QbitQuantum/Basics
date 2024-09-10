WINGDIAPI BOOL WINAPI wglMakeCurrent(HDC hdc, DHGLRC hglrc)
{
    if (!gCurrentContextSet)
    {
        gCurrentContext = gContexts.end();
        gCurrentContextSet = true;
    }

    if (!hdc || !hglrc)
    {
        gCurrentContext = gContexts.end();
        return 1;
    }

    int rc = (int)hglrc;

    if (gContexts.find(rc) == gCurrentContext)
    {
        return 1;
    }

    gCurrentContext = gContexts.find(rc);

    auto &xCtxt = gContexts[rc];
    OGL::State *pState = xCtxt.pState;

    HWND hWnd = WindowFromDC(hdc);
    RECT rect;
    GetClientRect(hWnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    SetOGL(pState);
    OGL::GetDDProcTable().pfnBindContext(OGL::GetDDHandle(), NULL, hWnd, NULL, width, height);

    // according to spec, only set current viewport to draw buffer dimensions if the context hasn't
    // been initialized
    if (!xCtxt.initialized)
    {
        pState->mViewport.x = 0;
        pState->mViewport.y = 0;
        pState->mViewport.width = width;
        pState->mViewport.height = height;
        pState->mScissor.x = 0;
        pState->mScissor.y = 0;
        pState->mScissor.width = width;
        pState->mScissor.height = height;
        xCtxt.initialized = true;
    }
    return 1;
}