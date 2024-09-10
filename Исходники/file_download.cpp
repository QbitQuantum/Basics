void WebLoadManager::sendRequest(webFileLoaderPrivate *loader, const QString &redirect) {
	Replies::iterator j = _replies.find(loader->reply());
	if (j != _replies.cend()) {
		QNetworkReply *r = j.key();
		_replies.erase(j);

		r->abort();
		r->deleteLater();
	}

	QNetworkReply *r = loader->request(_manager, redirect);
	connect(r, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onProgress(qint64, qint64)));
	connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onFailed(QNetworkReply::NetworkError)));
	connect(r, SIGNAL(metaDataChanged()), this, SLOT(onMeta()));
	_replies.insert(r, loader);
}