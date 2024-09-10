void SourceResolver::load(QMediaResourceList& resources, QIODevice* stream)
{
    QMutexLocker locker(&m_mutex);
    HRESULT hr = S_OK;
    if (!m_sourceResolver)
        hr = MFCreateSourceResolver(&m_sourceResolver);

    if (m_stream) {
        m_stream->Release();
        m_stream = NULL;
    }

    if (FAILED(hr)) {
        qWarning() << "Failed to create Source Resolver!";
        emit error(hr);
    } else if (stream) {
        if (resources.count() > 0) {
            QMediaResource resource = resources.takeFirst();
            QUrl url = resource.url();
            m_stream = new MFStream(stream, false);
            hr = m_sourceResolver->BeginCreateObjectFromByteStream(m_stream, reinterpret_cast<const OLECHAR *>(url.toString().utf16()),
                MF_RESOLUTION_MEDIASOURCE, NULL, &m_cancelCookie, this, new State(m_sourceResolver, true));
            if (FAILED(hr)) {
                qWarning() << "Unsupported stream!";
                emit error(hr);
            }
        } else {
            hr = MF_E_UNSUPPORTED_BYTESTREAM_TYPE;
            qWarning() << "Can't load stream without a hint of MIME type in a url";
            emit error(hr);
        }
    } else {
        QMediaResource resource = resources.takeFirst();
        QUrl url = resource.url();
#ifdef DEBUG_MEDIAFOUNDATION
        qDebug() << "loading :" << url;
        qDebug() << "url path =" << url.path().mid(1);
#endif
#ifdef TEST_STREAMING
        //Testing stream function
        if (url.scheme() == QLatin1String("file")) {
            stream = new QFile(url.path().mid(1), this);
            if (stream->open(QIODevice::ReadOnly)) {
                m_stream = new MFStream(stream, true);
                hr = m_sourceResolver->BeginCreateObjectFromByteStream(m_stream, reinterpret_cast<const OLECHAR *>(url.toString().utf16()),
                        MF_RESOLUTION_MEDIASOURCE, NULL, &m_cancelCookie, this, new State(m_sourceResolver, true));
                if (FAILED(hr)) {
                    qWarning() << "Unsupported stream!";
                    emit error(hr);
                }
            } else {
                delete stream;
                emit error(QMediaPlayer::FormatError);
            }
        } else
#endif
        if (url.scheme() == QLatin1String("qrc")) {
            // If the canonical URL refers to a Qt resource, open with QFile and use
            // the stream playback capability to play.
            stream = new QFile(QLatin1Char(':') + url.path(), this);
            if (stream->open(QIODevice::ReadOnly)) {
                m_stream = new MFStream(stream, true);
                hr = m_sourceResolver->BeginCreateObjectFromByteStream(m_stream, reinterpret_cast<const OLECHAR *>(url.toString().utf16()),
                         MF_RESOLUTION_MEDIASOURCE, NULL, &m_cancelCookie, this, new State(m_sourceResolver, true));
                if (FAILED(hr)) {
                    qWarning() << "Unsupported stream!";
                    emit error(hr);
                }
            } else {
                delete stream;
                emit error(QMediaPlayer::FormatError);
            }
        } else {
            hr = m_sourceResolver->BeginCreateObjectFromURL(reinterpret_cast<const OLECHAR *>(url.toString().utf16()),
                     MF_RESOLUTION_MEDIASOURCE, NULL, &m_cancelCookie, this, new State(m_sourceResolver, false));
            if (FAILED(hr)) {
                qWarning() << "Unsupported url scheme!";
                emit error(hr);
            }
        }
    }
}