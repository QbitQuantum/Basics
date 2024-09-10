void PluginView::updatePluginWidget()
{
    if (!parent())
        return;
    ASSERT(parent()->isFrameView());
    FrameView* frameView = static_cast<FrameView*>(parent());
    IntRect oldWindowRect = m_windowRect;
    IntRect oldClipRect = m_clipRect;
    
    m_windowRect = IntRect(frameView->contentsToWindow(frameRect().location()), frameRect().size());
    m_clipRect = windowClipRect();
    m_clipRect.move(-m_windowRect.x(), -m_windowRect.y());
    if (m_windowRect == oldWindowRect && m_clipRect == oldClipRect)
        return;

    // in order to move/resize the plugin window at the same time as the rest of frame
    // during e.g. scrolling, we set the mask and geometry in the paint() function, but
    // as paint() isn't called when the plugin window is outside the frame which can
    // be caused by a scroll, we need to move/resize immediately.
    if (!m_windowRect.intersects(frameView->frameRect()))
        setNPWindowIfNeeded();
}