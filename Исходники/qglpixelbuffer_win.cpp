bool QGLPixelBufferPrivate::init(const QSize &size, const QGLFormat &f, QGLWidget *shareWidget)
{
    QGLTemporaryContext tempContext;

    PFNWGLCREATEPBUFFERARBPROC wglCreatePbufferARB =
        (PFNWGLCREATEPBUFFERARBPROC) wglGetProcAddress("wglCreatePbufferARB");
    PFNWGLGETPBUFFERDCARBPROC wglGetPbufferDCARB =
        (PFNWGLGETPBUFFERDCARBPROC) wglGetProcAddress("wglGetPbufferDCARB");
    PFNWGLQUERYPBUFFERARBPROC wglQueryPbufferARB =
        (PFNWGLQUERYPBUFFERARBPROC) wglGetProcAddress("wglQueryPbufferARB");
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
        (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");

    if (!wglCreatePbufferARB) // assumes that if one can be resolved, all of them can
        return false;

    dc = wglGetCurrentDC();
    Q_ASSERT(dc);
    has_render_texture = false;

    // sample buffers doesn't work in conjunction with the render_texture extension
    if (!f.sampleBuffers()) {
        PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
                (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB) {
            QString extensions(QLatin1String(wglGetExtensionsStringARB(dc)));
            has_render_texture = extensions.contains(QLatin1String("WGL_ARB_render_texture"));
        }
    }

    int attribs[40];
    qt_format_to_attrib_list(has_render_texture, f, attribs);

    // Find pbuffer capable pixel format.
    unsigned int num_formats = 0;
    int pixel_format;
    wglChoosePixelFormatARB(dc, attribs, 0, 1, &pixel_format, &num_formats);

    // some GL implementations don't support pbuffers with accum
    // buffers, so try that before we give up
    if (num_formats == 0 && f.accum()) {
        QGLFormat tmp = f;
        tmp.setAccum(false);
        qt_format_to_attrib_list(has_render_texture, tmp, attribs);
        wglChoosePixelFormatARB(dc, attribs, 0, 1, &pixel_format, &num_formats);
    }

    if (num_formats == 0) {
        qWarning("QGLPixelBuffer: Unable to find a pixel format with pbuffer  - giving up.");
        return false;
    }
    format = pfiToQGLFormat(dc, pixel_format);

    // NB! The below ONLY works if the width/height are powers of 2.
    // Set some pBuffer attributes so that we can use this pBuffer as
    // a 2D RGBA texture target.
    int pb_attribs[] = {WGL_TEXTURE_FORMAT_ARB, WGL_TEXTURE_RGBA_ARB,
                        WGL_TEXTURE_TARGET_ARB, WGL_TEXTURE_2D_ARB, 0};
    int pb_attribs_null[] = {0};

    pbuf = wglCreatePbufferARB(dc, pixel_format, size.width(), size.height(),
                               has_render_texture ? pb_attribs : pb_attribs_null);
    if (!pbuf) {
        // try again without the render_texture extension
        pbuf = wglCreatePbufferARB(dc, pixel_format, size.width(), size.height(), pb_attribs_null);
        has_render_texture = false;
        if (!pbuf) {
            qWarning("QGLPixelBuffer: Unable to create pbuffer [w=%d, h=%d] - giving up.", size.width(), size.height());
            return false;
        }
    }

    dc = wglGetPbufferDCARB(pbuf);
    ctx = wglCreateContext(dc);
    if (!dc || !ctx) {
        qWarning("QGLPixelBuffer: Unable to create pbuffer context - giving up.");
        return false;
    }

    // Explicitly disable the render_texture extension if we have a 
    // multi-sampled pbuffer context. This seems to be a problem only with 
    // ATI cards if multi-sampling is forced globally in the driver.
    wglMakeCurrent(dc, ctx);
    GLint samples = 0;
    glGetIntegerv(GL_SAMPLES_ARB, &samples);
    if (has_render_texture && samples != 0)
        has_render_texture = false;

    HGLRC share_ctx = shareWidget ? shareWidget->d_func()->glcx->d_func()->rc : 0;
    if (share_ctx && !wglShareLists(share_ctx, ctx))
        qWarning("QGLPixelBuffer: Unable to share display lists - with share widget.");

    int width, height;
    wglQueryPbufferARB(pbuf, WGL_PBUFFER_WIDTH_ARB, &width);
    wglQueryPbufferARB(pbuf, WGL_PBUFFER_HEIGHT_ARB, &height);
    return true;
}