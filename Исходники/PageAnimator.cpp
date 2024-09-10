void PageAnimator::updateLayoutAndStyleForPainting(LocalFrame* rootFrame)
{
    RefPtr<FrameView> view = rootFrame->view();

    TemporaryChange<bool> servicing(m_updatingLayoutAndStyleForPainting, true);

    // In order for our child HWNDs (NativeWindowWidgets) to update properly,
    // they need to be told that we are updating the screen. The problem is that
    // the native widgets need to recalculate their clip region and not overlap
    // any of our non-native widgets. To force the resizing, call
    // setFrameRect(). This will be a quick operation for most frames, but the
    // NativeWindowWidgets will update a proper clipping region.
    view->setFrameRect(view->frameRect());

    // setFrameRect may have the side-effect of causing existing page layout to
    // be invalidated, so layout needs to be called last.
    view->updateLayoutAndStyleForPainting();
}