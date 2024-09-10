void EventTargetNode::dispatchWheelEvent(PlatformWheelEvent& e)
{
    assert(!eventDispatchForbidden());
    if (e.delta() == 0)
        return;
    
    FrameView* view = document()->view();
    if (!view)
        return;
    
    IntPoint pos = view->viewportToContents(e.pos());
    
    RefPtr<WheelEvent> we = new WheelEvent(e.isHorizontal(), e.delta(),
                                           document()->defaultView(), e.globalX(), e.globalY(), pos.x(), pos.y(),
                                           e.ctrlKey(), e.altKey(), e.shiftKey(), e.metaKey());
    ExceptionCode ec = 0;
    if (!dispatchEvent(we, ec, true))
        e.accept();
}