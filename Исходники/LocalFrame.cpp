PassOwnPtr<DragImage> LocalFrame::nodeImage(Node& node)
{
    if (!node.renderer())
        return nullptr;

    const ScopedFramePaintingState state(this, &node);

    m_view->updateLayoutAndStyleForPainting();

    m_view->setPaintBehavior(state.paintBehavior | PaintBehaviorFlattenCompositingLayers);

    m_view->setNodeToDraw(&node); // Enable special sub-tree drawing mode.

    // Document::updateLayout may have blown away the original RenderObject.
    RenderObject* renderer = node.renderer();
    if (!renderer)
        return nullptr;

    LayoutRect topLevelRect;
    IntRect paintingRect = pixelSnappedIntRect(renderer->paintingRootRect(topLevelRect));

    ASSERT(document()->isActive());
    float deviceScaleFactor = m_host->deviceScaleFactor();
    paintingRect.setWidth(paintingRect.width() * deviceScaleFactor);
    paintingRect.setHeight(paintingRect.height() * deviceScaleFactor);

    OwnPtr<ImageBuffer> buffer = ImageBuffer::create(paintingRect.size());
    if (!buffer)
        return nullptr;
    buffer->context()->scale(deviceScaleFactor, deviceScaleFactor);
    buffer->context()->translate(-paintingRect.x(), -paintingRect.y());
    buffer->context()->clip(FloatRect(0, 0, paintingRect.maxX(), paintingRect.maxY()));

    m_view->paintContents(buffer->context(), paintingRect);

    RefPtr<Image> image = buffer->copyImage();
    return DragImage::create(image.get(), renderer->shouldRespectImageOrientation(), deviceScaleFactor);
}