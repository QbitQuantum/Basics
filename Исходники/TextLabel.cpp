void TextLabel::paint(QPainter *p, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!m_hidden) {
        int i = 0; // lineHeight;
        int row = 1;
        int width = Meter::getWidth();
        int height = Meter::getHeight();
        QRect meterRect(0, 0, width, height);
        QRect textRect;
        QPoint next;

        p->setFont(font);
        if (scrollType != ScrollNone) {
            p->setClipRect(0, 0, width, height);
            if (!calculateScrollCoords(meterRect, textRect, next, 0, 0)) {
                p->setClipping(false);
                return;
            }
            width = textSize.width();
            height = textSize.height();
        }

        QStringList::Iterator it = value.begin();
        while (it != value.end() && (row <= height || height == -1)) {
            drawText(p, 0, 0 + i, width, height, *it);

            // Draw more instances of text if scroll type is normal scroll
            if (scrollType == ScrollNormal) {
                textRect.adjust(next.x(), next.y(), next.x(), next.y());
                while (textRect.intersects(meterRect)) {
                    drawText(p, textRect.x(), textRect.y() + i, width, height, *it);
                    textRect.adjust(next.x(), next.y(), next.x(), next.y());
                }
            }

            i += lineHeight;
            it++;
            row++;
        }

        if (scrollType != ScrollNone)
            p->setClipping(false);
    }
}