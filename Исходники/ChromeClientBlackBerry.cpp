bool ChromeClientBlackBerry::runJavaScriptConfirm(Frame* frame, const String& message)
{
#if ENABLE_DRT
    if (m_webPagePrivate->m_dumpRenderTree)
        return m_webPagePrivate->m_dumpRenderTree->runJavaScriptConfirm(message);
#endif

    TimerBase::fireTimersInNestedEventLoop();
    CString latinOrigin = frameOrigin(frame);
    return m_webPagePrivate->m_client->runJavaScriptConfirm(message.characters(), message.length(), latinOrigin.data(), latinOrigin.length());
}