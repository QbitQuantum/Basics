void PluginView::updatePluginWidget()
{
    if (!parent())
        return;

    ASSERT(parent()->isFrameView());
    FrameView* frameView = toFrameView(parent());

    IntRect oldWindowRect = m_windowRect;
    IntRect oldClipRect = m_clipRect;

    m_windowRect = IntRect(frameView->contentsToWindow(frameRect().location()), frameRect().size());
    m_clipRect = windowClipRect();
    m_clipRect.move(-m_windowRect.x(), -m_windowRect.y());

    if (m_windowRect == oldWindowRect && m_clipRect == oldClipRect)
        return;

    if (m_status != PluginStatusLoadedSuccessfully)
        return;

    if (!m_isWindowed && !m_windowRect.isEmpty()) {
        Display* display = getPluginDisplay(nullptr);
        if (m_drawable)
            XFreePixmap(display, m_drawable);
            
        m_drawable = XCreatePixmap(display, getRootWindow(m_parentFrame.get()),
            m_windowRect.width(), m_windowRect.height(),
            ((NPSetWindowCallbackStruct*)m_npWindow.ws_info)->depth);
        XSync(display, false); // make sure that the server knows about the Drawable
    }

    setNPWindowIfNeeded();
}