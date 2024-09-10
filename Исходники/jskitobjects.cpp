void JSKitXMLHttpRequest::send(const QJSValue &data)
{
    QByteArray byteData;

    if (data.isUndefined() || data.isNull()) {
        // Do nothing, byteData is empty.
    } else if (data.isString()) {
        byteData == data.toString().toUtf8();
    } else if (data.isObject()) {
        if (data.hasProperty("byteLength")) {
            // Looks like an ArrayView or an ArrayBufferView!
            QJSValue buffer = data.property("buffer");
            if (buffer.isUndefined()) {
                // We must assume we've been passed an ArrayBuffer directly
                buffer = data;
            }

            QJSValue array = data.property("_bytes");
            int byteLength = data.property("byteLength").toInt();

            if (array.isArray()) {
                byteData.reserve(byteLength);

                for (int i = 0; i < byteLength; i++) {
                    byteData.append(array.property(i).toInt());
                }

                qCDebug(l) << "passed an ArrayBufferView of" << byteData.length() << "bytes";
            } else {
                qCWarning(l) << "passed an unknown/invalid ArrayBuffer" << data.toString();
            }
        } else {
            qCWarning(l) << "passed an unknown object" << data.toString();
        }

    }

    QBuffer *buffer;
    if (!byteData.isEmpty()) {
        buffer = new QBuffer;
        buffer->setData(byteData);
    } else {
        buffer = 0;
    }

    qCDebug(l) << "sending" << _verb << "to" << _request.url() << "with" << QString::fromUtf8(byteData);
    _reply = _net->sendCustomRequest(_request, _verb.toLatin1(), buffer);

    connect(_reply, &QNetworkReply::finished,
            this, &JSKitXMLHttpRequest::handleReplyFinished);
    connect(_reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this, &JSKitXMLHttpRequest::handleReplyError);

    if (buffer) {
        // So that it gets deleted alongside the reply object.
        buffer->setParent(_reply);
    }
}