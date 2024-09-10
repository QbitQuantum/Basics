void QItemDelegate::doLayout(const QStyleOptionViewItem &option,
                             QRect *checkRect, QRect *pixmapRect, QRect *textRect,
                             bool hint) const
{
    Q_ASSERT(checkRect && pixmapRect && textRect);
    Q_D(const QItemDelegate);
    const QWidget *widget = d->widget(option);
    QStyle *style = widget ? widget->style() : QApplication::style();
    const bool hasCheck = checkRect->isValid();
    const bool hasPixmap = pixmapRect->isValid();
    const bool hasText = textRect->isValid();
    const int textMargin = hasText ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1 : 0;
    const int pixmapMargin = hasPixmap ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1 : 0;
    const int checkMargin = hasCheck ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1 : 0;
    int x = option.rect.left();
    int y = option.rect.top();
    int w, h;

    textRect->adjust(-textMargin, 0, textMargin, 0); // add width padding
    if (textRect->height() == 0 && (!hasPixmap || !hint)) {
        //if there is no text, we still want to have a decent height for the item sizeHint and the editor size
        textRect->setHeight(option.fontMetrics.height());
    }

    QSize pm(0, 0);
    if (hasPixmap) {
        pm = pixmapRect->size();
        pm.rwidth() += 2 * pixmapMargin;
    }
    if (hint) {
        h = qMax(checkRect->height(), qMax(textRect->height(), pm.height()));
        if (option.decorationPosition == QStyleOptionViewItem::Left
            || option.decorationPosition == QStyleOptionViewItem::Right) {
            w = textRect->width() + pm.width();
        } else {
            w = qMax(textRect->width(), pm.width());
        }
    } else {
        w = option.rect.width();
        h = option.rect.height();
    }

    int cw = 0;
    QRect check;
    if (hasCheck) {
        cw = checkRect->width() + 2 * checkMargin;
        if (hint) w += cw;
        if (option.direction == Qt::RightToLeft) {
            check.setRect(x + w - cw, y, cw, h);
        } else {
            check.setRect(x + checkMargin, y, cw, h);
        }
    }

    // at this point w should be the *total* width

    QRect display;
    QRect decoration;
    switch (option.decorationPosition) {
    case QStyleOptionViewItem::Top: {
        if (hasPixmap)
            pm.setHeight(pm.height() + pixmapMargin); // add space
        h = hint ? textRect->height() : h - pm.height();

        if (option.direction == Qt::RightToLeft) {
            decoration.setRect(x, y, w - cw, pm.height());
            display.setRect(x, y + pm.height(), w - cw, h);
        } else {
            decoration.setRect(x + cw, y, w - cw, pm.height());
            display.setRect(x + cw, y + pm.height(), w - cw, h);
        }
        break; }
    case QStyleOptionViewItem::Bottom: {
        if (hasText)
            textRect->setHeight(textRect->height() + textMargin); // add space
        h = hint ? textRect->height() + pm.height() : h;

        if (option.direction == Qt::RightToLeft) {
            display.setRect(x, y, w - cw, textRect->height());
            decoration.setRect(x, y + textRect->height(), w - cw, h - textRect->height());
        } else {
            display.setRect(x + cw, y, w - cw, textRect->height());
            decoration.setRect(x + cw, y + textRect->height(), w - cw, h - textRect->height());
        }
        break; }
    case QStyleOptionViewItem::Left: {
        if (option.direction == Qt::LeftToRight) {
            decoration.setRect(x + cw, y, pm.width(), h);
            display.setRect(decoration.right() + 1, y, w - pm.width() - cw, h);
        } else {
            display.setRect(x, y, w - pm.width() - cw, h);
            decoration.setRect(display.right() + 1, y, pm.width(), h);
        }
        break; }
    case QStyleOptionViewItem::Right: {
        if (option.direction == Qt::LeftToRight) {
            display.setRect(x + cw, y, w - pm.width() - cw, h);
            decoration.setRect(display.right() + 1, y, pm.width(), h);
        } else {
            decoration.setRect(x, y, pm.width(), h);
            display.setRect(decoration.right() + 1, y, w - pm.width() - cw, h);
        }
        break; }
    default:
        qWarning("doLayout: decoration position is invalid");
        decoration = *pixmapRect;
        break;
    }

    if (!hint) { // we only need to do the internal layout if we are going to paint
        *checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                         checkRect->size(), check);
        *pixmapRect = QStyle::alignedRect(option.direction, option.decorationAlignment,
                                          pixmapRect->size(), decoration);
        // the text takes up all available space, unless the decoration is not shown as selected
        if (option.showDecorationSelected)
            *textRect = display;
        else
            *textRect = QStyle::alignedRect(option.direction, option.displayAlignment,
                                            textRect->size().boundedTo(display.size()), display);
    } else {
        *checkRect = check;
        *pixmapRect = decoration;
        *textRect = display;
    }
}