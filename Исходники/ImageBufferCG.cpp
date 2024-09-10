void ImageBuffer::drawPattern(GraphicsContext& destContext, const FloatRect& srcRect, const AffineTransform& patternTransform, const FloatPoint& phase, const FloatSize& spacing, ColorSpace styleColorSpace, CompositeOperator op, const FloatRect& destRect, BlendMode blendMode)
{
    FloatRect adjustedSrcRect = srcRect;
    adjustedSrcRect.scale(m_resolutionScale, m_resolutionScale);

    if (!context().isAcceleratedContext()) {
        if (&destContext == &context() || destContext.isAcceleratedContext()) {
            if (RefPtr<Image> copy = copyImage(CopyBackingStore)) // Drawing into our own buffer, need to deep copy.
                copy->drawPattern(destContext, adjustedSrcRect, patternTransform, phase, spacing, styleColorSpace, op, destRect, blendMode);
        } else {
            if (RefPtr<Image> imageForRendering = copyImage(DontCopyBackingStore))
                imageForRendering->drawPattern(destContext, adjustedSrcRect, patternTransform, phase, spacing, styleColorSpace, op, destRect, blendMode);
        }
    } else {
        if (RefPtr<Image> copy = copyImage(CopyBackingStore))
            copy->drawPattern(destContext, adjustedSrcRect, patternTransform, phase, spacing, styleColorSpace, op, destRect, blendMode);
    }
}