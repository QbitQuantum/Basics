void FrameLoaderClientQt::download(WebCore::ResourceHandle* handle, const WebCore::ResourceRequest&, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&)
{
    if (!m_webFrame)
        return;

    QNetworkReplyHandler* handler = handle->getInternal()->m_job;
    QNetworkReply* reply = handler->release();
    if (reply) {
        QWebPage *page = m_webFrame->page();
        if (page->forwardUnsupportedContent())
            emit page->unsupportedContent(reply);
        else
            reply->abort();
    }
}