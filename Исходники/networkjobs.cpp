void CheckQuotaJob::start()
{
    QNetworkRequest req;
    req.setRawHeader("Depth", "0");
    QByteArray xml("<?xml version=\"1.0\" ?>\n"
                   "<d:propfind xmlns:d=\"DAV:\">\n"
                   "  <d:prop>\n"
                   "    <d:quota-available-bytes/>\n"
                   "    <d:quota-used-bytes/>\n"
                   "  </d:prop>\n"
                   "</d:propfind>\n");
    QBuffer *buf = new QBuffer(this);
    buf->setData(xml);
    buf->open(QIODevice::ReadOnly);
    // assumes ownership
    setReply(davRequest("PROPFIND", path(), req, buf));
    buf->setParent(reply());
    setupConnections(reply());
    AbstractNetworkJob::start();
}