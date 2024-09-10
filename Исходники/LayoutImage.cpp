bool LayoutImage::updateImageLoadingPriorities()
{
    if (!m_imageResource || !m_imageResource->cachedImage() || m_imageResource->cachedImage()->isLoaded())
        return false;

    LayoutRect viewBounds = viewRect();
    LayoutRect objectBounds = LayoutRect(absoluteContentBox());

    // The object bounds might be empty right now, so intersects will fail since it doesn't deal
    // with empty rects. Use LayoutRect::contains in that case.
    bool isVisible;
    if (!objectBounds.isEmpty())
        isVisible =  viewBounds.intersects(objectBounds);
    else
        isVisible = viewBounds.contains(objectBounds);

    ResourceLoadPriorityOptimizer::VisibilityStatus status = isVisible ?
        ResourceLoadPriorityOptimizer::Visible : ResourceLoadPriorityOptimizer::NotVisible;

    LayoutRect screenArea;
    if (!objectBounds.isEmpty()) {
        screenArea = viewBounds;
        screenArea.intersect(objectBounds);
    }

    ResourceLoadPriorityOptimizer::resourceLoadPriorityOptimizer()->notifyImageResourceVisibility(m_imageResource->cachedImage(), status, screenArea);

    return true;
}