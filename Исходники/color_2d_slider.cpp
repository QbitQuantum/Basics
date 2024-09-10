    void renderSquare(const QSize& size)
    {
        square = QImage(size, QImage::Format_RGB32);

        for ( int y = 0; y < size.height(); ++y )
        {
            qreal yfloat = 1 - qreal(y) / size.height();
            for ( int x = 0; x < size.width(); ++x )
            {
                qreal xfloat = qreal(x) / size.width();
                square.setPixel( x, y, QColor::fromHsvF(
                    PixHue(xfloat, yfloat),
                    PixSat(xfloat, yfloat),
                    PixVal(xfloat, yfloat)
                ).rgb());
            }
        }
    }