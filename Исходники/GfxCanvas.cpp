void GfxCanvasColor::paint(GfxPainter &p)
{
    qreal op = p.opacity();
    p.setOpacity(op * layerVisible());

    QSize s(int(_s.width() * layerScale()), int(_s.height() * layerScale()));
    if(_rotate.value()) {
        QMatrix m;
        m.translate(layerX(), layerY());
        m.rotate(_rotate.value());
        m.translate(-s.width() / 2, -s.height() / 2);
        p.fillRectTransformed(m, s, color(), quality().value() != 0.);
    } else {
        p.fillRect(QRect(QPoint(int(layerX() - qreal(s.width()) / 2.), 
                                int(layerY() - qreal(s.height()) / 2.)), s), color());
    }

    p.setOpacity(op);
    GfxCanvasItem::paint(p);
}