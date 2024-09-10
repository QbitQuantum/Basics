void PluginControllerProxy::handleMouseEvent(const WebMouseEvent& mouseEvent, PassRefPtr<Messages::PluginControllerProxy::HandleMouseEvent::DelayedReply> reply)
{
    // Always let the web process think that we've handled this mouse event, even before passing it along to the plug-in.
    // This is a workaround for 
    // <rdar://problem/9299901> UI process thinks the page is unresponsive when a plug-in is showing a context menu.
    // The web process sends a synchronous HandleMouseEvent message and the plug-in process spawns a nested
    // run loop when showing the context menu, so eventually the unresponsiveness timer kicks in in the UI process.
    // FIXME: We should come up with a better way to do this.
    reply->send(true);

    m_plugin->handleMouseEvent(mouseEvent);
}