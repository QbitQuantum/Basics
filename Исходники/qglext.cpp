static QGLMultiTextureExtensions *resolveMultiTextureExtensions
    (const QOpenGLContext *ctx)
{
    Q_ASSERT(ctx);
    if (!qt_multitexture_funcs)
        qt_multitexture_funcs = new QGLMultiTextureExtensions();
    if (!(qt_multitexture_funcs->multiTextureResolved)) {
        qt_multitexture_funcs->multiTextureResolved = true;
        if (!qt_multitexture_funcs->clientActiveTexture) {
            QOpenGLContext *vctx = const_cast<QOpenGLContext*>(ctx);
            qt_multitexture_funcs->clientActiveTexture = (q_PFNGLCLIENTACTIVETEXTUREPROC)
                vctx->getProcAddress("glClientActiveTexture");
        }
        if (!qt_multitexture_funcs->clientActiveTexture) {
            QOpenGLContext *vctx = const_cast<QOpenGLContext*>(ctx);
            qt_multitexture_funcs->clientActiveTexture = (q_PFNGLCLIENTACTIVETEXTUREPROC)
                vctx->getProcAddress("glClientActiveTextureARB");
        }
    }
    return qt_multitexture_funcs;
}