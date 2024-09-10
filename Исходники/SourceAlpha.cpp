void SourceAlpha::applySoftware()
{
    ImageBuffer* resultImage = createImageBufferResult();
    Filter* filter = this->filter();
    if (!resultImage || !filter->sourceImage())
        return;

    setIsAlphaImage(true);

    FloatRect imageRect(FloatPoint(), absolutePaintRect().size());
    GraphicsContext* filterContext = resultImage->context();
    filterContext->fillRect(imageRect, Color::black);

    IntRect srcRect = filter->sourceImageRect();
    if (ImageBuffer* sourceImageBuffer = filter->sourceImage()) {
        filterContext->drawImageBuffer(sourceImageBuffer,
            FloatRect(IntPoint(srcRect.location() - absolutePaintRect().location()), sourceImageBuffer->size()),
            0, CompositeDestinationIn);
    }
}