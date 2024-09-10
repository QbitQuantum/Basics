void FETile::applySoftware()
{
    FilterEffect* in = inputEffect(0);

    ImageBuffer* resultImage = createImageBufferResult();
    if (!resultImage)
        return;

    setIsAlphaImage(in->isAlphaImage());

    // Source input needs more attention. It has the size of the filterRegion but gives the
    // size of the cutted sourceImage back. This is part of the specification and optimization.
    FloatRect tileRect = in->maxEffectRect();
    FloatPoint inMaxEffectLocation = tileRect.location();
    FloatPoint maxEffectLocation = maxEffectRect().location();
    if (in->filterEffectType() == FilterEffectTypeSourceInput) {
        Filter* filter = this->filter();
        tileRect = filter->absoluteFilterRegion();
    }

    OwnPtr<ImageBufferSurface> surface;
    IntSize intTileSize = roundedIntSize(tileRect.size());
    surface = adoptPtr(new UnacceleratedImageBufferSurface(intTileSize));
    OwnPtr<ImageBuffer> tileImage = ImageBuffer::create(surface.release());
    if (!tileImage)
        return;

    GraphicsContext* tileImageContext = tileImage->context();
    tileImageContext->scale(FloatSize(intTileSize.width() / tileRect.width(), intTileSize.height() / tileRect.height()));
    tileImageContext->translate(-inMaxEffectLocation.x(), -inMaxEffectLocation.y());
    tileImageContext->drawImageBuffer(in->asImageBuffer(), in->absolutePaintRect().location());

    RefPtr<Pattern> pattern = Pattern::create(tileImage->copyImage(CopyBackingStore), true, true);

    AffineTransform patternTransform;
    patternTransform.translate(inMaxEffectLocation.x() - maxEffectLocation.x(), inMaxEffectLocation.y() - maxEffectLocation.y());
    pattern->setPatternSpaceTransform(patternTransform);
    GraphicsContext* filterContext = resultImage->context();
    filterContext->setFillPattern(pattern);
    filterContext->fillRect(FloatRect(FloatPoint(), absolutePaintRect().size()));
}