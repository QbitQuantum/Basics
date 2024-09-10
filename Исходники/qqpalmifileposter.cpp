////////////
/// \brief QQPalmiFilePoster::postFileUpload3TerOrg
/// \param file
///
QNetworkReply * QQPalmiFilePoster::postFileUpload3TerOrg(QFile *file)
{
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart filePart;
#if(QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	QMimeDatabase mimeDatabase;
	QMimeType mimeType = mimeDatabase.mimeTypeForFile(file->fileName(), QMimeDatabase::MatchDefault);
	filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mimeType.name()));
#else
	filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
#endif
	filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
					   QString("form-data; name=\"file\"; filename=\"%1\"").arg(file->fileName()));
	filePart.setBodyDevice(file);
	file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

	multiPart->append(filePart);

	QHttpPart timePart;
	timePart.setHeader(QNetworkRequest::ContentDispositionHeader,
					   QString("form-data; name=\"time\""));
	timePart.setBody(QString::fromLatin1("week").toLatin1());
	multiPart->append(timePart);

	QUrl url(QString("http://%1/script.php").arg(FILE_SHARING_SERVICE_JIRAFEAU_3TER_ORG));
	QNetworkRequest request(url);
	//request.setRawHeader("User-Agent", "Mozilla/5.0 (quteqoin)"); // Le service n'accepte pas l'ua par défaut ...
	//request.setRawHeader("Accept", "application/json, text/javascript, */*; q=0.01");
	//request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
	//request.setRawHeader("Accept-Encoding", "gzip, deflate"); // Qt 4 ne supporte pas gunzip nativement ....
	//request.setRawHeader("X-Requested-With", "XMLHttpRequest");
	request.setRawHeader("Referer", QString("http://%1/").arg(FILE_SHARING_SERVICE_JIRAFEAU_3TER_ORG).toLatin1());

	QNetworkReply *reply = httpPost(request, multiPart);
	multiPart->setParent(reply); // delete the multiPart with the reply

	return reply;
}