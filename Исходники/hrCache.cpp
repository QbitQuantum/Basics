GLuint hrCache::Load(const QImage &im) const
{
    QImage conv = QGLWidget::convertToGLFormat(target == GL_TEXTURE_2D
                                            ? ImageToPOT(im)
                                            : im
                                            );
    GLuint tx = bindImage(conv.bits()
                          , conv.width()
                          , conv.height()
                          , false
                          , 0
                          );
    return tx;
}