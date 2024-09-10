QVariant QXcbMime::mimeConvertToFormat(QXcbConnection *connection, xcb_atom_t a, const QByteArray &data, const QString &format,
                                       QVariant::Type requestedType, const QByteArray &encoding)
{
    QString atomName = mimeAtomToString(connection, a);
//    qDebug() << "mimeConvertDataToFormat" << format << atomName << data;

    if (!encoding.isEmpty()
        && atomName == format + QLatin1String(";charset=") + QString::fromLatin1(encoding)) {

#ifndef QT_NO_TEXTCODEC
        if (requestedType == QVariant::String) {
            QTextCodec *codec = QTextCodec::codecForName(encoding);
            if (codec)
                return codec->toUnicode(data);
        }
#endif

        return data;
    }

    // special cases for string types
    if (format == QLatin1String("text/plain")) {
        if (a == connection->atom(QXcbAtom::UTF8_STRING))
            return QString::fromUtf8(data);
        if (a == XCB_ATOM_STRING ||
            a == connection->atom(QXcbAtom::TEXT))
            return QString::fromLatin1(data);
    }

    // special case for uri types
    if (format == QLatin1String("text/uri-list")) {
        if (atomName == QLatin1String("text/x-moz-url")) {
            // we expect this as utf16 <url><space><title>
            // the first part is a url that should only contain ascci char
            // so it should be safe to check that the second char is 0
            // to verify that it is utf16
            if (data.size() > 1 && data.at(1) == 0)
                return QString::fromRawData((const QChar *)data.constData(),
                                data.size() / 2).split(QLatin1Char('\n')).first().toLatin1();
        }
    }

    if (atomName == format)
        return data;

#if 0 // ###
    // special case for images
    if (format == QLatin1String("image/ppm")) {
        if (a == XCB_ATOM_PIXMAP && data.size() == sizeof(Pixmap)) {
            Pixmap xpm = *((Pixmap*)data.data());
            if (!xpm)
                return QByteArray();
            Window root;
            int x;
            int y;
            uint width;
            uint height;
            uint border_width;
            uint depth;

            XGetGeometry(display, xpm, &root, &x, &y, &width, &height, &border_width, &depth);
            XImage *ximg = XGetImage(display,xpm,x,y,width,height,AllPlanes,depth==1 ? XYPixmap : ZPixmap);
            QImage qimg = QXlibStatic::qimageFromXImage(ximg);
            XDestroyImage(ximg);

            QImageWriter imageWriter;
            imageWriter.setFormat("PPMRAW");
            QBuffer buf;
            buf.open(QIODevice::WriteOnly);
            imageWriter.setDevice(&buf);
            imageWriter.write(qimg);
            return buf.buffer();
        }
    }
#endif
    return QVariant();
}