void DroidStoreAPI::getDownloadURL(QByteArray packageid, QByteArray evozi_key)
{
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart packageidPart;
	packageidPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"packagename\""));
	packageidPart.setBody(packageid);
	multiPart->append(packageidPart);

	QHttpPart apikeyPart;
	apikeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_key\""));
	apikeyPart.setBody(evozi_key);
	multiPart->append(apikeyPart);

	QUrl url(downloadURL);
	QNetworkRequest request(url);

	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QNetworkReply *reply = manager->post(request, multiPart);
	multiPart->setParent(reply);

	connect(reply, SIGNAL(finished()), this, SLOT(onComplete()));
}