// Checks if |node| is offscreen the visible area (viewport) of its container
// document. In case it is, one can scroll in direction or take any different
// desired action later on.
bool hasOffscreenRect(Node* node, FocusType type)
{
    // Get the FrameView in which |node| is (which means the current viewport if |node|
    // is not in an inner document), so we can check if its content rect is visible
    // before we actually move the focus to it.
    FrameView* frameView = node->document().view();
    if (!frameView)
        return true;

    ASSERT(!frameView->needsLayout());

    LayoutRect containerViewportRect = frameView->visibleContentRect();
    // We want to select a node if it is currently off screen, but will be
    // exposed after we scroll. Adjust the viewport to post-scrolling position.
    // If the container has overflow:hidden, we cannot scroll, so we do not pass direction
    // and we do not adjust for scrolling.
    switch (type) {
    case FocusTypeLeft:
        containerViewportRect.setX(containerViewportRect.x() - ScrollableArea::pixelsPerLineStep());
        containerViewportRect.setWidth(containerViewportRect.width() + ScrollableArea::pixelsPerLineStep());
        break;
    case FocusTypeRight:
        containerViewportRect.setWidth(containerViewportRect.width() + ScrollableArea::pixelsPerLineStep());
        break;
    case FocusTypeUp:
        containerViewportRect.setY(containerViewportRect.y() - ScrollableArea::pixelsPerLineStep());
        containerViewportRect.setHeight(containerViewportRect.height() + ScrollableArea::pixelsPerLineStep());
        break;
    case FocusTypeDown:
        containerViewportRect.setHeight(containerViewportRect.height() + ScrollableArea::pixelsPerLineStep());
        break;
    default:
        break;
    }

    RenderObject* render = node->renderer();
    if (!render)
        return true;

    LayoutRect rect(render->absoluteClippedOverflowRect());
    if (rect.isEmpty())
        return true;

    return !containerViewportRect.intersects(rect);
}