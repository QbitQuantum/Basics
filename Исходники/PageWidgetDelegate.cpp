void PageWidgetDelegate::layout(Page* page)
{
    RefPtr<FrameView> view = mainFrameView(page);
    if (!view)
        return;
    // In order for our child HWNDs (NativeWindowWidgets) to update properly,
    // they need to be told that we are updating the screen. The problem is that
    // the native widgets need to recalculate their clip region and not overlap
    // any of our non-native widgets. To force the resizing, call
    // setFrameRect(). This will be a quick operation for most frames, but the
    // NativeWindowWidgets will update a proper clipping region.
    view->setFrameRect(view->frameRect());

    // setFrameRect may have the side-effect of causing existing page layout to
    // be invalidated, so layout needs to be called last.
    view->updateLayoutAndStyleIfNeededRecursive();

    // For now, as we know this is the point in code where the compositor has
    // actually asked for Blink to update the composited layer tree. So finally
    // do all the deferred work for updateCompositingLayers() here.
    if (RenderView* renderView = view->renderView())
        renderView->compositor()->updateCompositingLayers(CompositingUpdateFinishAllDeferredWork);
}