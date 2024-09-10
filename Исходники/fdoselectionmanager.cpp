void FdoSelectionManagerPrivate::handleCancelMessage(const XClientMessageEvent &event)
{
    const WId winId = event.window;
    const long messageId = event.data.l[2];

    if (messageRequests.contains(winId) && messageRequests[winId].messageId == messageId) {
        messageRequests.remove(winId);
    }
}