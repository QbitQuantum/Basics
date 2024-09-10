void DuokanScreen::blit12To4(const QImage &image,
                             const QPoint &topLeft, const QRegion &region)
{
    image.save("/mnt/us/DK_System/duokan/b.png", "png");
    const int imageStride = image.bytesPerLine() / 2;
    const QVector<QRect> rects = region.rects();
    int scolor ;

    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i).translated(-topLeft);
        int y = r.y();
        const quint16 *s = reinterpret_cast<const quint16*>(image.scanLine(y));

        while (y <= r.bottom()) {
            int x1 = r.x();
            while (x1 <= r.right()) {
                const quint16 c = s[x1];
                int x2 = x1;
                // find span length
                while ((x2+1 < r.right()) && (s[x2+1] == c))
                    ++x2;

                scolor = alloc((c>>8) & 0x0f, (c>>4) & 0x0f, c & 0x0f) ;

                k4_hline(x1 + topLeft.x(), y + topLeft.y(), x2 + topLeft.x(), scolor);

                x1 = x2 + 1;
            }
            s += imageStride;
            ++y;
        }
    }

    QImage trans_image((const uchar*)(base()), dw, dh, pixelFormat());
    trans_image.save("/mnt/us/DK_System/duokan/c.png", "png");
}