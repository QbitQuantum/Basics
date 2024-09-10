void ImgurUploader::upload(QNetworkAccessManager *net, UploadItemPtr item, const QVariant &data)
{
  m_net = net;

  const QVariantMap map       = data.toMap();
  const QVariantList authData = map.value(LS("a")).toList();

  if (authData.size() == 3) {
    m_clientId     = authData.at(0).toString();
    m_clientSecret = authData.at(1).toString();

    m_queue.enqueue(item);
    getToken(ChatId(ChatId::MessageId), "refresh_token", authData.value(2).toByteArray(), authData);
    return;
  }

  QNetworkReply *reply = 0;

  if (item->type() == ImageItem::Type) {
    ImageItem *i = uploaditem_cast<ImageItem*>(item.data());

    QHttpPart image;
    image.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    image.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"" + DateTime::toDateTime(item->date()).toString(LS("yyyy-MM-dd_hh-mm-ss")).toLatin1() + ".png\"");
    image.setBody(i->raw);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->append(image);

    if (!item->title().isEmpty()) {
      QHttpPart title;
      title.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\""));
      title.setBody(item->title().toUtf8());
      multiPart->append(title);
    }

    QNetworkRequest request(QUrl(LS("https://api.imgur.com/3/image")));
    request.setRawHeader("User-Agent", OsInfo::userAgent());

    if (authData.size() == 4)
      request.setRawHeader("Authorization", "Bearer " + authData.value(3).toByteArray());
    else
      request.setRawHeader("Authorization", "Client-ID " + authData.value(0).toByteArray());

    reply = net->post(request, multiPart);
    multiPart->setParent(reply);
  }

  prepare(reply, item->id());
}