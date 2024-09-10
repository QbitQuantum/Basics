PassRefPtr<WebImage> InjectedBundleRangeHandle::renderedImage(SnapshotOptions options)
{
    Document& ownerDocument = m_range->ownerDocument();
    Frame* frame = ownerDocument.frame();
    if (!frame)
        return nullptr;

    FrameView* frameView = frame->view();
    if (!frameView)
        return nullptr;

    Ref<Frame> protector(*frame);

    VisibleSelection oldSelection = frame->selection().selection();
    frame->selection().setSelection(VisibleSelection(*m_range));

    float scaleFactor = (options & SnapshotOptionsExcludeDeviceScaleFactor) ? 1 : frame->page()->deviceScaleFactor();
    IntRect paintRect = enclosingIntRect(m_range->absoluteBoundingRect());
    IntSize backingStoreSize = paintRect.size();
    backingStoreSize.scale(scaleFactor);

    RefPtr<ShareableBitmap> backingStore = ShareableBitmap::createShareable(backingStoreSize, ShareableBitmap::SupportsAlpha);
    if (!backingStore)
        return nullptr;

    auto graphicsContext = backingStore->createGraphicsContext();
    graphicsContext->scale(scaleFactor);

    paintRect.move(frameView->frameRect().x(), frameView->frameRect().y());
    paintRect.moveBy(-frameView->scrollPosition());

    graphicsContext->translate(-paintRect.x(), -paintRect.y());

    PaintBehavior oldPaintBehavior = frameView->paintBehavior();
    PaintBehavior paintBehavior = oldPaintBehavior | PaintBehaviorSelectionOnly | PaintBehaviorFlattenCompositingLayers;
    if (options & SnapshotOptionsForceBlackText)
        paintBehavior |= PaintBehaviorForceBlackText;
    if (options & SnapshotOptionsForceWhiteText)
        paintBehavior |= PaintBehaviorForceWhiteText;

    frameView->setPaintBehavior(paintBehavior);
    ownerDocument.updateLayout();

    frameView->paint(*graphicsContext, paintRect);
    frameView->setPaintBehavior(oldPaintBehavior);

    frame->selection().setSelection(oldSelection);

    return WebImage::create(backingStore);
}