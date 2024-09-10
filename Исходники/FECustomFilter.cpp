void FECustomFilter::platformApplySoftware()
{
    Uint8ClampedArray* dstPixelArray = createPremultipliedImageResult();
    if (!dstPixelArray)
        return;

    FilterEffect* in = inputEffect(0);
    IntRect effectDrawingRect = requestedRegionOfInputImageData(in->absolutePaintRect());
    RefPtr<Uint8ClampedArray> srcPixelArray = in->asPremultipliedImage(effectDrawingRect);
    
    IntSize newContextSize(effectDrawingRect.size());
    bool hadContext = m_context;
    if (!m_context)
        initializeContext();
    
    if (!hadContext || m_contextSize != newContextSize)
        resizeContext(newContextSize);

    // Do not draw the filter if the input image cannot fit inside a single GPU texture.
    if (m_inputTexture->tiles().numTilesX() != 1 || m_inputTexture->tiles().numTilesY() != 1)
        return;
    
    // The shader had compiler errors. We cannot draw anything.
    if (!m_shader->isInitialized())
        return;

    m_context->bindFramebuffer(GraphicsContext3D::FRAMEBUFFER, m_frameBuffer);
    m_context->viewport(0, 0, newContextSize.width(), newContextSize.height());
    
    m_context->clearColor(0, 0, 0, 0);
    m_context->clear(GraphicsContext3D::COLOR_BUFFER_BIT | GraphicsContext3D::DEPTH_BUFFER_BIT);
    
    bindProgramAndBuffers(srcPixelArray.get());
    
    m_context->drawElements(GraphicsContext3D::TRIANGLES, m_mesh->indicesCount(), GraphicsContext3D::UNSIGNED_SHORT, 0);
    
    ASSERT(static_cast<size_t>(newContextSize.width() * newContextSize.height() * 4) == dstPixelArray->length());
    m_context->readPixels(0, 0, newContextSize.width(), newContextSize.height(), GraphicsContext3D::RGBA, GraphicsContext3D::UNSIGNED_BYTE, dstPixelArray->data());
}