QNetworkReply * Pillow::HttpHandlerProxy::createProxiedReply(Pillow::HttpConnection *request, QNetworkRequest proxiedRequest)
{
	QBuffer* requestContentBuffer = NULL;
	if (request->requestContent().size() > 0)
	{
		requestContentBuffer = new QBuffer(&(const_cast<QByteArray&>(request->requestContent())));
		requestContentBuffer->open(QIODevice::ReadOnly);
	}

	QNetworkReply* proxiedReply = _networkAccessManager->sendCustomRequest(proxiedRequest, request->requestMethod(), requestContentBuffer);

	if (requestContentBuffer) requestContentBuffer->setParent(proxiedReply);

	return proxiedReply;
}