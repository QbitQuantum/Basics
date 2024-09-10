// API Candidate?
void DumpRenderTreeSupportQt::setAlternateHtml(QWebFrameAdapter* adapter, const QString& html, const QUrl& baseUrl, const QUrl& failingUrl)
{
    KURL kurl(baseUrl);
    WebCore::Frame* coreFrame = adapter->frame;
    WebCore::ResourceRequest request(kurl);
    const QByteArray utf8 = html.toUtf8();
    WTF::RefPtr<WebCore::SharedBuffer> data = WebCore::SharedBuffer::create(utf8.constData(), utf8.length());
    WebCore::SubstituteData substituteData(data, WTF::String("text/html"), WTF::String("utf-8"), failingUrl);
    coreFrame->loader()->load(WebCore::FrameLoadRequest(coreFrame, request, substituteData));
}