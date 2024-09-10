void IconDelegate::doLayout(const QStyleOptionViewItem &option,
                             QRect *checkRect, QRect *pixmapRect, QRect *textRect,
                             bool hint) const
{
    Q_ASSERT(checkRect && pixmapRect && textRect);
    int x = option.rect.left();
    int y = option.rect.top();
    int w, h;

    textRect->adjust(-textMargin, 0, textMargin, 0); // add width padding

    QSize pm(0, 0);
    if (pixmapRect->isValid())
        pm = option.decorationSize;
    if (hint) {
        w = qMax(textRect->width(), pm.width());
        h = qMax(textRect->height(), pm.height());
    } else {
        w = option.rect.width();
        h = option.rect.height();
    }

    int cw = 0;
    QRect check;
    if (checkRect->isValid()) {
        check.setRect(x, y, checkRect->width() + textMargin * 2, h);
        cw = check.width();
        if (option.direction == Qt::LeftToRight)
            x += cw;
    }

    QRect display;
    QRect decoration;
    QStyleOptionViewItem::Position position = option.decorationPosition;
    if (option.direction == Qt::RightToLeft) {
        if (position == QStyleOptionViewItem::Right)
            position = QStyleOptionViewItem::Left;
        else if (position == QStyleOptionViewItem::Left)
            position = QStyleOptionViewItem::Right;
    }
    switch (position) {
    case QStyleOptionViewItem::Top: {
        if (!pm.isEmpty())
            pm.setHeight(pm.height() + textMargin); // add space
        decoration.setRect(x, y, w, pm.height());
        h = hint ? textRect->height() : h - pm.height();
        display.setRect(x, y + pm.height(), w, h);
        break; }
    case QStyleOptionViewItem::Bottom: {
        if (!textRect->isEmpty())
            textRect->setHeight(textRect->height() + textMargin); // add space
        h = hint ? textRect->height() + pm.height() : h;
        decoration.setRect(x, y + h - pm.height(), w, pm.height());
        h = hint ? textRect->height() : h - pm.height();
        display.setRect(x, y, w, h);
        break; }
    case QStyleOptionViewItem::Left: {
        if (!pm.isEmpty())
            pm.setWidth(pm.width() + textMargin); // add space
        decoration.setRect(x, y, pm.width(), h);
        w = hint ? textRect->width() : w - pm.width() - cw;
        display.setRect(x + pm.width(), y, w, h);
        break; }
    case QStyleOptionViewItem::Right: {
        if (!textRect->isEmpty())
            textRect->setWidth(textRect->width() + textMargin); // add space
        w = hint ? textRect->width() + pm.width() : w;
        decoration.setRect(x + w - pm.width() - cw, y, pm.width(), h);
        w = hint ? textRect->width() : w - pm.width() - cw;
        display.setRect(x, y, w, h);
        break; }
    default:
        qWarning("doLayout: decoration positon is invalid");
        decoration = *pixmapRect;
        break;
    }

    if (!hint) { // we only need to do the internal layout if we are going to paint
        *checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                         checkRect->size(), check);
        *pixmapRect = QStyle::alignedRect(option.direction, option.decorationAlignment,
                                          pixmapRect->size(), decoration);
    } else {
        *checkRect = check;
        *pixmapRect = decoration;
    }
    *textRect = display;
}