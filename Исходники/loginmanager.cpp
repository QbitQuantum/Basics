void LoginManager::upload(const QString &path, int nid, const QString &title, const QString &description, const QString& priv, const QString& license, const QString& tags, const QString& changes)
      {
#if ! 0 // see further down
      Q_UNUSED(changes);
#endif
      qDebug() << "file upload" << nid;
//       KQOAuthRequest *oauthRequest = new KQOAuthRequest(this);
//       QUrl url(QString("https://%1/services/rest/score.json").arg(MUSESCORE_HOST));
//       if (nid > 0)
//             url = QUrl(QString("https://%1/services/rest/score/%2/update.json").arg(MUSESCORE_HOST).arg(nid));

      ApiRequest r = ApiRequestBuilder()
         .setPath("/score/upload")
         .setToken(_accessToken)
         .build();

      QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

      QHttpPart filePart;
      filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
      QString contentDisposition = QString("form-data; name=\"score_data\"; filename=\"temp_%1.mscz\"").arg(qrand() % 100000);
      filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(contentDisposition));
      QFile *file = new QFile(path);
      file->open(QIODevice::ReadOnly);
      filePart.setBodyDevice(file);
      file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
      multiPart->append(filePart);

      if (nid > 0) {
            QHttpPart idPart;
            qDebug() << "added idPart";
            idPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"score_id\""));
            idPart.setBody(QString::number(nid).toLatin1()); // TODO: check
            multiPart->append(idPart);
            }

      QHttpPart titlePart;
      titlePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\""));
      titlePart.setBody(title.toUtf8());
      multiPart->append(titlePart);

      QHttpPart descriptionPart;
      descriptionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
      descriptionPart.setBody(description.toUtf8());
      multiPart->append(descriptionPart);

      QHttpPart privatePart;
      privatePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"private\""));
      privatePart.setBody(priv.toUtf8());
      multiPart->append(privatePart);

      QHttpPart licensePart;
      licensePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"license\""));
      licensePart.setBody(license.toUtf8());
      multiPart->append(licensePart);

      QHttpPart tagsPart;
      tagsPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"tags\""));
      tagsPart.setBody(tags.toUtf8());
      multiPart->append(tagsPart);

#if 0 // TODO: what is this and is this now supported?
      if (nid > 0) {
            QHttpPart changesPart;
            changesPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"revision_log\""));
            changesPart.setBody(changes.toUtf8());
            multiPart->append(changesPart);
      }
#endif

      // TODO: "uri" parameter?
      QNetworkReply* reply;
      if (nid > 0) // score exists, update
            reply = _networkManager->put(r.request, multiPart);
      else // score doesn't exist, post a new score
            reply = _networkManager->post(r.request, multiPart);

      connect(reply, &QNetworkReply::finished, this, [this, reply] {
            onReplyFinished(reply, RequestType::UPLOAD_SCORE);
            });
     }