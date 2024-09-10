//----------------------------------------------------------------------------//
void OpenGLWGLPBTextureTarget::initialisePBuffer()
{
    int creation_attrs[] =
    {
        WGL_PBUFFER_LARGEST_ARB, true,
        0
    };

    releasePBuffer();

    HDC hdc = wglGetCurrentDC();
    d_pbuffer = wglCreatePbufferARB(hdc, d_pixfmt, 
                                    static_cast<int>(d_area.getWidth()),
                                    static_cast<int>(d_area.getHeight()),
                                    creation_attrs);

    if (!d_pbuffer)
        CEGUI_THROW(RendererException(
            "OpenGLWGLPBTextureTarget::initialisePBuffer - "
            "pbuffer creation failure, wglCreatePbufferARB() call failed."));

    d_hdc = wglGetPbufferDCARB(d_pbuffer);

    if (!d_hdc)
        CEGUI_THROW(RendererException(
            "OpenGLWGLPBTextureTarget::initialisePBuffer - "
            "pbuffer creation failure, wglGetPbufferDCARB() call failed."));

    d_context= wglCreateContext(d_hdc);

    if (!d_hdc)
        CEGUI_THROW(RendererException(
            "OpenGLWGLPBTextureTarget::initialisePBuffer - "
            "pbuffer creation failure, wglCreateContext() call failed."));

    if(!wglShareLists(wglGetCurrentContext(), d_context))
        CEGUI_THROW(RendererException(
            "OpenGLWGLPBTextureTarget::initialisePBuffer - "
            "pbuffer creation failure, wglShareLists() call failed."));

    // extract the actual size of the created bufer
    int actual_width, actual_height;
    wglQueryPbufferARB(d_pbuffer, WGL_PBUFFER_WIDTH_ARB, &actual_width);
    wglQueryPbufferARB(d_pbuffer, WGL_PBUFFER_HEIGHT_ARB, &actual_height);
    d_area.setSize(Size(static_cast<float>(actual_width),
                        static_cast<float>(actual_height)));

    // ensure CEGUI::Texture is wrapping real GL texture and has correct size
    d_CEGUITexture->setOpenGLTexture(d_texture, d_area.getSize());
}