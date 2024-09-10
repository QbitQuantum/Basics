void ImageBuffer::drawPattern(GraphicsContext* context, const FloatRect& srcRect, const AffineTransform& patternTransform,
                              const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator op, const FloatRect& destRect)
{
    ASSERT(context);
    RefPtr<Image> imageCopy = copyImage(CopyBackingStore);
    imageCopy->drawPattern(context, srcRect, patternTransform, phase, styleColorSpace, op, destRect);
}