//! [0]
bool DBScreen::initDevice()
{
    if (!QLinuxFbScreen::initDevice())
        return false;

    QScreenCursor::initSoftwareCursor();
    image = new QImage(deviceWidth(), deviceHeight(), pixelFormat());
    painter = new QPainter(image);

    return true;
}