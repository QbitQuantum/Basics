void LayerTextureUpdaterSkPicture::updateTextureRect(GraphicsContext3D* compositorContext, TextureAllocator* allocator, ManagedTexture* texture, const IntRect& sourceRect, const IntRect& destRect)
{
    ASSERT(!m_context || m_context == compositorContext);
    m_context = compositorContext;

    if (m_createFrameBuffer) {
        deleteFrameBuffer();
        createFrameBuffer();
        m_createFrameBuffer = false;
    }
    if (!m_fbo)
        return;

    // Bind texture.
    context()->bindFramebuffer(GraphicsContext3D::FRAMEBUFFER, m_fbo);
    texture->framebufferTexture2D(context(), allocator);
    ASSERT(context()->checkFramebufferStatus(GraphicsContext3D::FRAMEBUFFER) == GraphicsContext3D::FRAMEBUFFER_COMPLETE);

    // Make sure SKIA uses the correct GL context.
    context()->makeContextCurrent();

    GrContext* skiaContext = m_context->grContext();
    // Notify SKIA to sync its internal GL state.
    skiaContext->resetContext();
    m_canvas->save();
    m_canvas->clipRect(SkRect(destRect));
    // Translate the origin of contentRect to that of destRect.
    // Note that destRect is defined relative to sourceRect.
    m_canvas->translate(contentRect().x() - sourceRect.x() + destRect.x(),
                        contentRect().y() - sourceRect.y() + destRect.y());
    m_canvas->drawPicture(m_picture);
    m_canvas->restore();
    // Flush SKIA context so that all the rendered stuff appears on the texture.
    skiaContext->flush();

    // Unbind texture.
    context()->framebufferTexture2D(GraphicsContext3D::FRAMEBUFFER, GraphicsContext3D::COLOR_ATTACHMENT0, GraphicsContext3D::TEXTURE_2D, 0, 0);
    context()->bindFramebuffer(GraphicsContext3D::FRAMEBUFFER, 0);
}