ImageBitmap::ImageBitmap(HTMLVideoElement* video, const IntRect& cropRect)
    : m_imageElement(nullptr)
    , m_cropRect(cropRect)
    , m_bitmapOffset(IntPoint())
{
    IntSize playerSize;

    if (video->webMediaPlayer())
        playerSize = video->webMediaPlayer()->naturalSize();

    IntRect videoRect = IntRect(IntPoint(), playerSize);
    IntRect srcRect = intersection(cropRect, videoRect);
    IntRect dstRect(IntPoint(), srcRect.size());

    OwnPtr<ImageBuffer> buffer = ImageBuffer::create(videoRect.size());
    if (!buffer)
        return;

    OwnPtr<GraphicsContext> extraGraphicsContext;
    OwnPtr<DisplayItemList> displayItemList;
    GraphicsContext* context;
    if (RuntimeEnabledFeatures::slimmingPaintEnabled()) {
        displayItemList = DisplayItemList::create();
        extraGraphicsContext = adoptPtr(new GraphicsContext(0, displayItemList.get()));
        context = extraGraphicsContext.get();
    } else {
        context = buffer->context();
    }

    {
        DrawingRecorder recorder(context, buffer->displayItemClient(), DisplayItem::VideoBitmap, videoRect);
        context->clip(dstRect);
        context->translate(-srcRect.x(), -srcRect.y());
    }

    if (RuntimeEnabledFeatures::slimmingPaintEnabled())
        displayItemList->replay(buffer->context());

    video->paintCurrentFrameInContext(buffer->context(), videoRect);
    m_bitmap = buffer->copyImage(DontCopyBackingStore);
    m_bitmapRect = IntRect(IntPoint(std::max(0, -cropRect.x()), std::max(0, -cropRect.y())), srcRect.size());
}