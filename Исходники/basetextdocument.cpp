bool BaseTextDocument::open(const QString &fileName)
{
    QString title = tr("untitled");
    if (!fileName.isEmpty()) {
        const QFileInfo fi(fileName);
        m_fileName = fi.absoluteFilePath();

        QFile file(fileName);
        if (!file.exists())
            return false;

        if (!fi.isReadable())
            return false;

        if (!fi.isWritable()) {
            if (!file.open(QIODevice::ReadOnly))
                return false;
        } else {
            if (!file.open(QIODevice::ReadWrite))
                return false;
        }
        title = fi.fileName();

        QByteArray buf = file.readAll();
        int bytesRead = buf.size();

        QTextCodec *codec = m_codec;

        // code taken from qtextstream
        if (bytesRead >= 4 && ((uchar(buf[0]) == 0xff && uchar(buf[1]) == 0xfe && uchar(buf[2]) == 0 && uchar(buf[3]) == 0)
                               || (uchar(buf[0]) == 0 && uchar(buf[1]) == 0 && uchar(buf[2]) == 0xfe && uchar(buf[3]) == 0xff))) {
            codec = QTextCodec::codecForName("UTF-32");
        } else if (bytesRead >= 2 && ((uchar(buf[0]) == 0xff && uchar(buf[1]) == 0xfe)
                                      || (uchar(buf[0]) == 0xfe && uchar(buf[1]) == 0xff))) {
            codec = QTextCodec::codecForName("UTF-16");
        } else if (!codec) {
            codec = QTextCodec::codecForLocale();
        }
        // end code taken from qtextstream

        m_codec = codec;

#if 0 // should work, but does not, Qt bug with "system" codec
        QTextDecoder *decoder = m_codec->makeDecoder();
        QString text = decoder->toUnicode(buf);
        m_hasDecodingError = (decoder->hasFailure());
        delete decoder;
#else
        QString text = m_codec->toUnicode(buf);
        QByteArray verifyBuf = m_codec->fromUnicode(text); // slow
        // the minSize trick lets us ignore unicode headers
        int minSize = qMin(verifyBuf.size(), buf.size());
        m_hasDecodingError = (minSize < buf.size()- 4
                              || memcmp(verifyBuf.constData() + verifyBuf.size() - minSize,
                                        buf.constData() + buf.size() - minSize, minSize));
#endif

        if (m_hasDecodingError) {
            int p = buf.indexOf('\n', 16384);
            if (p < 0)
                m_decodingErrorSample = buf;
            else
                m_decodingErrorSample = buf.left(p);
        } else {
            m_decodingErrorSample.clear();
        }

        int lf = text.indexOf('\n');
        if (lf > 0 && text.at(lf-1) == QLatin1Char('\r')) {
            m_lineTerminatorMode = CRLFLineTerminator;
        } else if (lf >= 0) {
            m_lineTerminatorMode = LFLineTerminator;
        } else {
            m_lineTerminatorMode = NativeLineTerminator;
        }

        m_document->setModified(false);
        m_document->setUndoRedoEnabled(false);
        if (m_isBinaryData)
            m_document->setHtml(tr("<em>Binary data</em>"));
        else
            m_document->setPlainText(text);
        m_document->setUndoRedoEnabled(true);
        TextEditDocumentLayout *documentLayout = qobject_cast<TextEditDocumentLayout*>(m_document->documentLayout());
        QTC_ASSERT(documentLayout, return true);
        documentLayout->lastSaveRevision = 0;
        m_document->setModified(false);
        emit titleChanged(title);
        emit changed();
    }
    return true;
}