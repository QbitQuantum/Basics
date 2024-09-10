bool
makeCurrent(Drawable *drawable, Context *context)
{
    if (!drawable || !context) {
        return wglMakeCurrent(NULL, NULL);
    } else {
        WglDrawable *wglDrawable = static_cast<WglDrawable *>(drawable);
        WglContext *wglContext = static_cast<WglContext *>(context);

        if (!wglContext->hglrc) {
            wglContext->hglrc = wglCreateContext(wglDrawable->hDC);
            if (!wglContext->hglrc) {
                std::cerr << "error: wglCreateContext failed\n";
                exit(1);
                return false;
            }
            if (wglContext->shareContext) {
                BOOL bRet;
                bRet = wglShareLists(wglContext->shareContext->hglrc,
                                     wglContext->hglrc);
                if (!bRet) {
                    std::cerr << "warning: wglShareLists failed\n";
                }
            }
        }

        return wglMakeCurrent(wglDrawable->hDC, wglContext->hglrc);
    }
}