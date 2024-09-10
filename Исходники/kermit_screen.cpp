// Ref: http://doc.trolltech.com/4.2/qtopiacore-svgalib.html
// http://doc.trolltech.com/main-snapshot/ipc-sharedmemory-dialog-cpp.html
bool KermitScreen::connect(const QString &displaySpec)
{
    Q_UNUSED(displaySpec);

    // Read environment variables.
    int width = qgetenv("SCREEN_WIDTH").toInt();
    int height = qgetenv("SCREEN_HEIGHT").toInt();

    // Fallback if not available.
    if (width <= 0)
    {
        width = DEFAULT_WIDTH;
    }
    if (height <= 0)
    {
        height = DEFAULT_HEIGHT;
    }

    QScreen::d = 32;                     // Color depth.

    QScreen::lstep = width * d / 8;
    QScreen::w = width;
    QScreen::h = height;
    QScreen::dw = width;
    QScreen::dh = height;

    QScreen::size = lstep * height;
    QScreen::grayscale = false;

    setPixelFormat(QImage::Format_ARGB32);

    if (memory_ == 0)
    {
        memory_ = new uchar[size];
        mapsize = size;
        qDebug("map size is %d in argb", mapsize);
    }
    QScreen::data = memory_;

    // Maybe need to change the dpi later.
    const int dpi = 72;
    QScreen::physWidth = qRound(QScreen::dw * 25.4 / dpi);
    QScreen::physHeight = qRound(QScreen::dh * 25.4 / dpi);
    return true;
}