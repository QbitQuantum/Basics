bool QVFbScreen::connect(const QString &displaySpec)
{
    QStringList displayArgs = displaySpec.split(QLatin1Char(':'));
    if (displayArgs.contains(QLatin1String("Gray")))
        grayscale = true;

    key_t key = ftok(QT_VFB_MOUSE_PIPE(displayId).toLocal8Bit(), 'b');

    if (key == -1)
        return false;

#if Q_BYTE_ORDER == Q_BIG_ENDIAN
#ifndef QT_QWS_FRAMEBUFFER_LITTLE_ENDIAN
    if (displayArgs.contains(QLatin1String("littleendian")))
#endif
        QScreen::setFrameBufferLittleEndian(true);
#endif

    int shmId = shmget(key, 0, 0);
    if (shmId != -1)
        d_ptr->shmrgn = (unsigned char *)shmat(shmId, 0, 0);
    else
        return false;

    if ((long)d_ptr->shmrgn == -1 || d_ptr->shmrgn == 0) {
        qDebug("No shmrgn %ld", (long)d_ptr->shmrgn);
        return false;
    }

    d_ptr->hdr = (QVFbHeader *)d_ptr->shmrgn;
    data = d_ptr->shmrgn + d_ptr->hdr->dataoffset;

    dw = w = d_ptr->hdr->width;
    dh = h = d_ptr->hdr->height;
    d = d_ptr->hdr->depth;

    switch (d) {
    case 1:
        setPixelFormat(QImage::Format_Mono);
        break;
    case 8:
        setPixelFormat(QImage::Format_Indexed8);
        break;
    case 12:
        setPixelFormat(QImage::Format_RGB444);
        break;
    case 15:
        setPixelFormat(QImage::Format_RGB555);
        break;
    case 16:
        setPixelFormat(QImage::Format_RGB16);
        break;
    case 18:
        setPixelFormat(QImage::Format_RGB666);
        break;
    case 24:
        setPixelFormat(QImage::Format_RGB888);
        break;
    case 32:
        setPixelFormat(QImage::Format_ARGB32_Premultiplied);
        break;
    }

    lstep = d_ptr->hdr->linestep;

    // Handle display physical size spec.
    int dimIdxW = -1;
    int dimIdxH = -1;
    for (int i = 0; i < displayArgs.size(); ++i) {
        if (displayArgs.at(i).startsWith(QLatin1String("mmWidth"))) {
            dimIdxW = i;
            break;
        }
    }
    for (int i = 0; i < displayArgs.size(); ++i) {
        if (displayArgs.at(i).startsWith(QLatin1String("mmHeight"))) {
            dimIdxH = i;
            break;
        }
    }
    if (dimIdxW >= 0) {
        bool ok;
        int pos = 7;
        if (displayArgs.at(dimIdxW).at(pos) == QLatin1Char('='))
            ++pos;
        int pw = displayArgs.at(dimIdxW).mid(pos).toInt(&ok);
        if (ok) {
            physWidth = pw;
            if (dimIdxH < 0)
                physHeight = dh*physWidth/dw;
        }
    }
    if (dimIdxH >= 0) {
        bool ok;
        int pos = 8;
        if (displayArgs.at(dimIdxH).at(pos) == QLatin1Char('='))
            ++pos;
        int ph = displayArgs.at(dimIdxH).mid(pos).toInt(&ok);
        if (ok) {
            physHeight = ph;
            if (dimIdxW < 0)
                physWidth = dw*physHeight/dh;
        }
    }
    if (dimIdxW < 0 && dimIdxH < 0) {
        const int dpi = 72;
        physWidth = qRound(dw * 25.4 / dpi);
        physHeight = qRound(dh * 25.4 / dpi);
    }

    qDebug("Connected to VFB server %s: %d x %d x %d %dx%dmm (%dx%ddpi)", displaySpec.toLatin1().data(),
        w, h, d, physWidth, physHeight, qRound(dw*25.4/physWidth), qRound(dh*25.4/physHeight) );

    size = lstep * h;
    mapsize = size;
    screencols = d_ptr->hdr->numcols;
    memcpy(screenclut, d_ptr->hdr->clut, sizeof(QRgb) * screencols);

    connected = this;

    if (qgetenv("QT_QVFB_BGR").toInt())
        pixeltype = BGRPixel;

    return true;
}