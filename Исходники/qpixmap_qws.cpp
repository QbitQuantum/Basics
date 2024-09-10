QT_BEGIN_NAMESPACE

QPixmap QPixmap::grabWindow(WId window, int x, int y, int w, int h)
{
    QWidget *widget = QWidget::find(window);
    if (!widget)
        return QPixmap();

    QRect grabRect = widget->frameGeometry();
    if (!widget->isWindow())
        grabRect.translate(widget->parentWidget()->mapToGlobal(QPoint()));
    if (w < 0)
        w = widget->width() - x;
    if (h < 0)
        h = widget->height() - y;
    grabRect &= QRect(x, y, w, h).translated(widget->mapToGlobal(QPoint()));

    QScreen *screen = qt_screen;
    QDesktopWidget *desktop = QApplication::desktop();
    if (!desktop)
        return QPixmap();
    if (desktop->numScreens() > 1) {
        const int screenNo = desktop->screenNumber(widget);
        if (screenNo != -1)
            screen = qt_screen->subScreens().at(screenNo);
        grabRect = grabRect.translated(-screen->region().boundingRect().topLeft());
    }

    if (screen->pixelFormat() == QImage::Format_Invalid) {
        qWarning("QPixmap::grabWindow(): Unable to copy pixels from framebuffer");
        return QPixmap();
    }

    if (screen->isTransformed()) {
        const QSize screenSize(screen->width(), screen->height());
        grabRect = screen->mapToDevice(grabRect, screenSize);
    }

    QWSDisplay::grab(false);
    QPixmap pixmap;
    QImage img(screen->base(),
               screen->deviceWidth(), screen->deviceHeight(),
               screen->linestep(), screen->pixelFormat());
    img = img.copy(grabRect);
    QWSDisplay::ungrab();

    if (screen->isTransformed()) {
        QMatrix matrix;
        switch (screen->transformOrientation()) {
        case 1: matrix.rotate(90); break;
        case 2: matrix.rotate(180); break;
        case 3: matrix.rotate(270); break;
        default: break;
        }
        img = img.transformed(matrix);
    }

    if (screen->pixelType() == QScreen::BGRPixel)
        img = img.rgbSwapped();

    return QPixmap::fromImage(img);
}