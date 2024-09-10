void Usage::registerUsage() {
	if (! g.s.bUsage || g.s.uiUpdateCounter == 0) // Only register usage if allowed by the user and first wizard run has finished
		return;

	QDomDocument doc;
	QDomElement root=doc.createElement(QLatin1String("usage"));
	doc.appendChild(root);

	QDomElement tag;
	QDomText t;

	OSInfo::fillXml(doc, root);

	tag=doc.createElement(QLatin1String("in"));
	root.appendChild(tag);
	t=doc.createTextNode(g.s.qsAudioInput);
	tag.appendChild(t);

	tag=doc.createElement(QLatin1String("out"));
	root.appendChild(tag);
	t=doc.createTextNode(g.s.qsAudioOutput);
	tag.appendChild(t);

	tag=doc.createElement(QLatin1String("lcd"));
	root.appendChild(tag);
	t=doc.createTextNode(QString::number(g.lcd->hasDevices() ? 1 : 0));
	tag.appendChild(t);

	QBuffer *qb = new QBuffer();
	qb->setData(doc.toString().toUtf8());
	qb->open(QIODevice::ReadOnly);

	QNetworkRequest req(QUrl(QLatin1String("http://mumble.info/usage.cgi")));
	Network::prepareRequest(req);
	req.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("text/xml"));

	QNetworkReply *rep = g.nam->post(req, qb);
	qb->setParent(rep);

	connect(rep, SIGNAL(finished()), rep, SLOT(deleteLater()));
}