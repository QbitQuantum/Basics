void MetaDetector::updateMediaFileTagCodec(MediaMeta *meta, const QByteArray &codecName, bool forceEncode)
{
    Q_ASSERT(meta != nullptr);

    if (meta->localPath.isEmpty()) {
        qCritical() << "meta localPath is empty:" << meta->title << meta->hash;
        return ;
    }

    QByteArray detectByte;
    QByteArray detectCodec = codecName;
    auto mediaPath = QStringToTString(meta->localPath);
#ifdef _WIN32
    TagLib::FileRef f(meta->localPath.toStdWString().c_str());
#else
    TagLib::FileRef f(meta->localPath.toStdString().c_str());
#endif
    TagLib::Tag *tag = f.tag();

    if (!f.file()) {
        qCritical() << "TagLib: open file failed:" << meta->localPath << f.file();
    }

    if (!tag) {
        qWarning() << "TagLib: no tag for media file" << meta->localPath;
        return;
    }

    bool encode = true;
    encode &= tag->title().isNull() ? true : tag->title().isLatin1();
    encode &= tag->artist().isNull() ? true : tag->artist().isLatin1();
    encode &= tag->album().isNull() ? true : tag->album().isLatin1();

    if (forceEncode) {
        encode = true;
    }

    if (encode) {
        if (detectCodec.isEmpty()) {
            detectByte += tag->title().toCString();
            detectByte += tag->artist().toCString();
            detectByte += tag->album().toCString();
            detectCodec = detectEncodings(detectByte).value(0);
//            qDebug() << "detect codec" << detectEncodings(detectByte);
        }

//        qDebug() << "convert to" << detectCodec;
//        QTextCodec *codec = QTextCodec::codecForName(detectCodec);
//        meta->album = codec->toUnicode(tag->album().to8Bit().c_str());
//        meta->artist = codec->toUnicode(tag->artist().to8Bit().c_str());
//        meta->title = codec->toUnicode(tag->title().to8Bit().c_str());

//#ifndef true
//        qDebug() << "convert to" << detectCodec << QTextCodec::availableCodecs();
        const size_t buflen = 1024 * 10;
        char buf[buflen];
        UErrorCode err = U_ZERO_ERROR;
        int32_t len = ucnv_convert("utf-8", detectCodec, buf, buflen, tag->title().toCString(), -1, &err);
        meta->title = QString::fromUtf8(buf);
//        qDebug() << len <<  QString::fromUtf8(buf) << buf << u_errorName(err);

        err = U_ZERO_ERROR;
        len = ucnv_convert("utf-8", detectCodec, buf, buflen, tag->artist().toCString(), -1, &err);
        meta->artist = QString::fromUtf8(buf);
//        qDebug() << len <<  QString::fromUtf8(buf) << buf << u_errorName(err);

        err = U_ZERO_ERROR;
        len = ucnv_convert("utf-8", detectCodec, buf, buflen, tag->album().toCString(), -1, &err);
        meta->album = QString::fromUtf8(buf);
//        qDebug() << len <<  QString::fromUtf8(buf) << buf << u_errorName(err);
        Q_UNUSED(len);
//#endif
    } else {
        meta->album = TStringToQString(tag->album());
        meta->artist = TStringToQString(tag->artist());
        meta->title = TStringToQString(tag->title());
    }

    if (meta->title.isEmpty()) {
        QFileInfo localFi(meta->localPath);
        meta->title = localFi.completeBaseName();
    }
}