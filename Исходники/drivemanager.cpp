	void DriveManager::handleUploadRequestFinished ()
	{
		QNetworkReply *reply = qobject_cast<QNetworkReply*> (sender ());
		if (!reply)
			return;

		reply->deleteLater ();
		QString path = Reply2FilePath_.take (reply);

		const int code = reply->
				attribute (QNetworkRequest::HttpStatusCodeAttribute).toInt ();
		if (code != 200)
		{
			qWarning () << Q_FUNC_INFO
					<< "upload initiating failed with code:"
					<< code;
			return;
		}

		emit uploadStatusChanged (tr ("Uploading..."), path);

		QFile *file = new QFile (path);
		if (!file->open (QIODevice::ReadOnly))
		{
			qWarning () << Q_FUNC_INFO
					<< "unable to open file: "
					<< file->errorString ();
			return;
		}

		QUrl url (reply->rawHeader ("Location"));
		QNetworkRequest request (url);
#ifdef HAVE_MAGIC
		request.setHeader (QNetworkRequest::ContentTypeHeader,
				magic_file (Magic_, path.toUtf8 ()));
#endif
		request.setHeader (QNetworkRequest::ContentLengthHeader,
				QString::number (QFileInfo (path).size ()).toUtf8 ());

		QNetworkReply *uploadReply = Core::Instance ().GetProxy ()->
				GetNetworkAccessManager ()->put (request, file);
		file->setParent (uploadReply);
		Reply2FilePath_ [uploadReply] = path;

		connect (uploadReply,
				SIGNAL (finished ()),
				this,
				SLOT (handleUploadFinished ()));
		connect (uploadReply,
				SIGNAL (error (QNetworkReply::NetworkError)),
				this,
				SLOT (handleUploadError (QNetworkReply::NetworkError)));
		connect (uploadReply,
				SIGNAL (uploadProgress (qint64, qint64)),
				this,
				SLOT (handleUploadProgress (qint64, qint64)));
	}