QPixmap MusicItem::changeColor(const QPixmap &pixmap, QColor c)
{
    QImage image = pixmap.toImage();
    QRgb old;
    int width = pixmap.width();
    int height = pixmap.height();
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            old = image.pixel(i, j);
            if (qAlpha(old) == 255)
                image.setPixel(i, j, c.rgb());
        }
    }

    return pixmap.fromImage(image);
}