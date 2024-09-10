void GeneratorGeneratedImage::drawPattern(GraphicsContext* destContext, const FloatRect& srcRect, const AffineTransform& patternTransform,
                                 const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator compositeOp, const FloatRect& destRect)
{
    // Allow the generator to provide visually-equivalent tiling parameters for better performance.
    IntSize adjustedSize = m_size;
    FloatRect adjustedSrcRect = srcRect;
    m_generator->adjustParametersForTiledDrawing(adjustedSize, adjustedSrcRect);

    // Factor in the destination context's scale to generate at the best resolution
    AffineTransform destContextCTM = destContext->getCTM();
    double xScale = fabs(destContextCTM.xScale());
    double yScale = fabs(destContextCTM.yScale());
    AffineTransform adjustedPatternCTM = patternTransform;
    adjustedPatternCTM.scale(1.0 / xScale, 1.0 / yScale);
    adjustedSrcRect.scale(xScale, yScale);

    unsigned generatorHash = m_generator->hash();

    if (!m_cachedImageBuffer
        || m_cachedGeneratorHash != generatorHash
        || m_cachedAdjustedSize != adjustedSize
        || !destContext->isCompatibleWithBuffer(m_cachedImageBuffer.get())) {
        // Create a BitmapImage and call drawPattern on it.
        m_cachedImageBuffer = destContext->createCompatibleBuffer(adjustedSize);
        if (!m_cachedImageBuffer)
            return;

        // Fill with the generated image.
        GraphicsContext* graphicsContext = m_cachedImageBuffer->context();
        graphicsContext->fillRect(FloatRect(FloatPoint(), adjustedSize), *m_generator.get());

        m_cachedGeneratorHash = generatorHash;
        m_cachedAdjustedSize = adjustedSize;
    }

    // Tile the image buffer into the context.
    m_cachedImageBuffer->drawPattern(destContext, adjustedSrcRect, adjustedPatternCTM, phase, styleColorSpace, compositeOp, destRect);
    m_cacheTimer.restart();
}