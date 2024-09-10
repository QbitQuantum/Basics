QImage::Format
QWSMemorySurface::preferredImageFormat(const QWidget *widget) const
{
    QScreen *screen = getScreen(widget);
    const int depth = screen->depth();
    const bool opaque = isWidgetOpaque(widget);

    if (!opaque) {
        if (depth <= 12)
            return QImage::Format_ARGB4444_Premultiplied;
        else if (depth <= 15)
            return QImage::Format_ARGB8555_Premultiplied;
        else if (depth <= 16)
            return QImage::Format_ARGB8565_Premultiplied;
        else if (depth <= 18)
            return QImage::Format_ARGB6666_Premultiplied;
        else
            return QImage::Format_ARGB32_Premultiplied;
    }

    QImage::Format format = screen->pixelFormat();
    if (format > QImage::Format_Indexed8) // ### assumes all new image formats supports a QPainter
        return format;

    if (depth <= 12)
        return QImage::Format_RGB444;
    else if (depth <= 15)
        return QImage::Format_RGB555;
    else if (depth <= 16)
        return QImage::Format_RGB16;
    else if (depth <= 18)
        return QImage::Format_RGB666;
    else if (depth <= 24)
        return QImage::Format_RGB888;
    else
        return QImage::Format_ARGB32_Premultiplied;
}