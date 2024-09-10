std::pair<SafeByteArray, size_t> BOSHConnection::createHTTPRequest(const SafeByteArray& data, bool streamRestart, bool terminate, unsigned long long rid, const std::string& sid, const URL& boshURL) {
    size_t size;
    std::stringstream content;
    SafeByteArray contentTail = createSafeByteArray("</body>");
    std::stringstream header;

    content << "<body rid='" << rid << "' sid='" << sid << "'";
    if (streamRestart) {
        content << " xmpp:restart='true' xmlns:xmpp='urn:xmpp:xbosh'";
    }
    if (terminate) {
        content << " type='terminate'";
    }
    content << " xmlns='http://jabber.org/protocol/httpbind'>";

    SafeByteArray safeContent = createSafeByteArray(content.str());
    safeContent.insert(safeContent.end(), data.begin(), data.end());
    safeContent.insert(safeContent.end(), contentTail.begin(), contentTail.end());

    size = safeContent.size();

    header    << "POST " << boshURL.getPath() << " HTTP/1.1\r\n"
            << "Host: " << boshURL.getHost();
    if (boshURL.getPort()) {
            header << ":" << *boshURL.getPort();
    }
    header    << "\r\n"
        // << "Accept-Encoding: deflate\r\n"
            << "Content-Type: text/xml; charset=utf-8\r\n"
            << "Content-Length: " << size << "\r\n\r\n";

    SafeByteArray safeHeader = createSafeByteArray(header.str());
    safeHeader.insert(safeHeader.end(), safeContent.begin(), safeContent.end());

    return std::pair<SafeByteArray, size_t>(safeHeader, size);
}