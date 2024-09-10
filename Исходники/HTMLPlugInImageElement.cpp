void HTMLPlugInImageElement::subframeLoaderWillCreatePlugIn(const KURL& url)
{
    if (!document()->page()
        || !document()->page()->settings()->plugInSnapshottingEnabled())
        return;

    bool inMainFrame = document()->frame() == document()->page()->mainFrame();

    if (document()->isPluginDocument() && inMainFrame) {
        LOG(Plugins, "%p Plug-in document in main frame", this);
        return;
    }

    if (ScriptController::processingUserGesture()) {
        LOG(Plugins, "%p Script is processing user gesture, set to play", this);
        return;
    }

    if (m_createdDuringUserGesture) {
        LOG(Plugins, "%p Plug-in was created when processing user gesture, set to play", this);
        return;
    }

    double lastKnownUserGestureTimestamp = document()->lastHandledUserGestureTimestamp();
    if (!inMainFrame && document()->page()->mainFrame() && document()->page()->mainFrame()->document())
        lastKnownUserGestureTimestamp = std::max(lastKnownUserGestureTimestamp, document()->page()->mainFrame()->document()->lastHandledUserGestureTimestamp());
    if (currentTime() - lastKnownUserGestureTimestamp < autostartSoonAfterUserGestureThreshold) {
        LOG(Plugins, "%p Plug-in was created shortly after a user gesture, set to play", this);
        return;
    }

    RenderBox* renderEmbeddedObject = toRenderBox(renderer());
    Length styleWidth = renderEmbeddedObject->style()->width();
    Length styleHeight = renderEmbeddedObject->style()->height();
    LayoutRect contentBoxRect = renderEmbeddedObject->contentBoxRect();
    int contentWidth = contentBoxRect.width();
    int contentHeight = contentBoxRect.height();
    int contentArea = contentWidth * contentHeight;
    IntSize visibleViewSize = document()->frame()->view()->visibleSize();
    int visibleArea = visibleViewSize.width() * visibleViewSize.height();

    if (inMainFrame && styleWidth.isPercent() && (styleWidth.percent() == 100)
        && styleHeight.isPercent() && (styleHeight.percent() == 100)
        && (static_cast<float>(contentArea) / visibleArea > sizingFullPageAreaRatioThreshold)) {
        LOG(Plugins, "%p Plug-in is top level full page, set to play", this);
        return;
    }

    if (contentWidth <= sizingTinyDimensionThreshold || contentHeight <= sizingTinyDimensionThreshold) {
        LOG(Plugins, "%p Plug-in is %dx%d, set to play", this, contentWidth, contentHeight);
        return;
    }

    if (!document()->page() || !document()->page()->plugInClient()) {
        setDisplayState(WaitingForSnapshot);
        return;
    }

    LOG(Plugins, "%p Plug-in URL: %s", this, m_url.utf8().data());
    LOG(Plugins, "            loaded URL: %s", url.string().utf8().data());

    m_plugInOriginHash = PlugInOriginHash::hash(this, url);
    if (m_plugInOriginHash && document()->page()->plugInClient()->isAutoStartOrigin(m_plugInOriginHash)) {
        LOG(Plugins, "%p Plug-in hash %x is auto-start, set to play", this, m_plugInOriginHash);
        return;
    }

    LOG(Plugins, "%p Plug-in hash %x is %dx%d, origin is not auto-start, set to wait for snapshot", this, m_plugInOriginHash, contentWidth, contentHeight);
    // We may have got to this point by restarting a snapshotted plug-in, in which case we don't want to
    // reset the display state.
    if (displayState() != PlayingWithPendingMouseClick)
        setDisplayState(WaitingForSnapshot);
}