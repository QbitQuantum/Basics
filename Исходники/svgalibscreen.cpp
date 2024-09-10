//! [5]
void SvgalibScreen::blit(const QImage &img, const QPoint &topLeft,
                         const QRegion &reg)
{
    if (depth() == 8) {
        switch (img.format()) {
        case QImage::Format_RGB16:
            blit16To8(img, topLeft, reg);
            return;
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            blit32To8(img, topLeft, reg);
            return;
        default:
            break;
        }
    }

    if (img.format() != pixelFormat()) {
        if (base())
            QScreen::blit(img, topLeft, reg);
        return;
    }

    const QVector<QRect> rects = (reg & region()).rects();

    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i);
        gl_putboxpart(r.x(), r.y(), r.width(), r.height(),
                      img.width(), img.height(),
                      static_cast<void*>(const_cast<uchar*>(img.bits())),
                      r.x() - topLeft.x(), r.y() - topLeft.y());
    }
}