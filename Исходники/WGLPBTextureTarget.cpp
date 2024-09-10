//----------------------------------------------------------------------------//
OpenGLWGLPBTextureTarget::OpenGLWGLPBTextureTarget(OpenGLRendererBase& owner) :
    OpenGLTextureTarget(owner),
    d_pixfmt(0),
    d_pbuffer(0),
    d_context(0),
    d_hdc(0),
    d_prevContext(0),
    d_prevDC(0)
{
    if (!WGLEW_ARB_pbuffer)
        CEGUI_THROW(RendererException("WGL_ARB_pbuffer extension is needed to "
            "use OpenGLWGLPBTextureTarget!"));

    HDC hdc = wglGetCurrentDC();

    uint fmtcnt;
    wglChoosePixelFormatARB(hdc, pbAttrs, 0, 1, &d_pixfmt, &fmtcnt);

    if (!fmtcnt)
        CEGUI_THROW(RendererException(
            "pbuff creation failure, no suitable pixel formats."));

    initialiseTexture();

    // set default size (and cause initialisation of the pbuffer)
    declareRenderSize(Sizef(DEFAULT_SIZE, DEFAULT_SIZE));
}