void BitmapTexture::updateContents(TextureMapper* textureMapper, GraphicsLayer* sourceLayer, const IntRect& targetRect, const IntPoint& offset, UpdateContentsFlag updateContentsFlag)
{
    OwnPtr<ImageBuffer> imageBuffer = ImageBuffer::create(targetRect.size());
    GraphicsContext* context = imageBuffer->context();
    context->setImageInterpolationQuality(textureMapper->imageInterpolationQuality());
    context->setTextDrawingMode(textureMapper->textDrawingMode());

    IntRect sourceRect(targetRect);
    sourceRect.setLocation(offset);
    context->translate(-offset.x(), -offset.y());
    sourceLayer->paintGraphicsLayerContents(*context, sourceRect);

    RefPtr<Image> image = imageBuffer->copyImage(DontCopyBackingStore);

    updateContents(image.get(), targetRect, IntPoint(), updateContentsFlag);
}