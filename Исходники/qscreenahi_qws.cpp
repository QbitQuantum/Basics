void QAhiScreen::solidFill(const QColor &color, const QRegion &reg)
{
    AhiSts_t status = AhiStsOk;

    switch (pixelFormat()) {
    case QImage::Format_ARGB32_Premultiplied:
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
        status = AhiDrawBrushFgColorSet(d_ptr->context, color.rgba());
        break;
    case QImage::Format_RGB16:
        status = AhiDrawBrushFgColorSet(d_ptr->context, qt_convRgbTo16(color.rgb()));
        break;
    default:
        qFatal("QAhiScreen::solidFill(): Not implemented for pixel format %d",
               int(pixelFormat()));
        break;
    }

    if (status != AhiStsOk) {
        qWarning("QAhiScreen::solidFill(): AhiDrawBrushFgColorSet failed: %x",
                 status);
        return;
    }

    status = AhiDrawBrushSet(d_ptr->context, 0, 0, 0, AHIFLAG_BRUSHSOLID);
    if (status != AhiStsOk) {
        qWarning("QAhiScreen::solidFill(): AhiDrawBrushSet failed: %x",
                 status);
        return;
    }

    status = AhiDrawRopSet(d_ptr->context, AHIMAKEROP3(AHIROPPATCOPY));
    if (status != AhiStsOk) {
        qWarning("QAhiScreen::solidFill(): AhiDrawRopSet failed: %x", status);
        return;
    }

    status = AhiDrawSurfDstSet(d_ptr->context, d_ptr->surface, 0);
    if (status != AhiStsOk) {
        qWarning("QAhiScreen::solidFill(): AhiDrawSurfDst failed: %x", status);
        return;
    }

    const QVector<QRect> rects = (reg & region()).rects();
    QVarLengthArray<AhiRect_t> ahiRects(rects.size());

    for (int i = 0; i < rects.size(); ++i) {
        const QRect rect = rects.at(i);
        ahiRects[i].left = rect.left();
        ahiRects[i].top = rect.top();
        ahiRects[i].right = rect.x() + rect.width();
        ahiRects[i].bottom = rect.y() + rect.height();
    }

    status = AhiDrawBitBltMulti(d_ptr->context, ahiRects.data(),
                                0, ahiRects.size());
    if (status != AhiStsOk)
        qWarning("QAhiScreen::solidFill(): AhiDrawBitBlt failed: %x", status);
}