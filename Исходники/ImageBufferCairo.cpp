RefPtr<Image> ImageBuffer::sinkIntoImage(std::unique_ptr<ImageBuffer> imageBuffer, ScaleBehavior scaleBehavior)
{
    return imageBuffer->copyImage(DontCopyBackingStore, scaleBehavior);
}