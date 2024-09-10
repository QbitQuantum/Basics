static void blitTexture(QGLContext *ctx, GLuint texture, const QSize &viewport, const QSize &texSize, const QRect &targetRect, const QRect &sourceRect)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
    glViewport(0, 0, viewport.width(), viewport.height());

    QGLShaderProgram *blitProgram =
        QGLEngineSharedShaders::shadersForContext(ctx)->blitProgram();
    blitProgram->bind();
    blitProgram->setUniformValue("imageTexture", 0 /*QT_IMAGE_TEXTURE_UNIT*/);

    // The shader manager's blit program does not multiply the
    // vertices by the pmv matrix, so we need to do the effect
    // of the orthographic projection here ourselves.
    QRectF r;
    qreal w = viewport.width();
    qreal h = viewport.height();
    r.setLeft((targetRect.left() / w) * 2.0f - 1.0f);
    if (targetRect.right() == (viewport.width() - 1))
        r.setRight(1.0f);
    else
        r.setRight((targetRect.right() / w) * 2.0f - 1.0f);
    r.setBottom((targetRect.top() / h) * 2.0f - 1.0f);
    if (targetRect.bottom() == (viewport.height() - 1))
        r.setTop(1.0f);
    else
        r.setTop((targetRect.bottom() / w) * 2.0f - 1.0f);

    drawTexture(r, texture, texSize, sourceRect);
}