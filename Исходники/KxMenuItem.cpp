void KxMenuItemWidget::paintEvent(QPaintEvent *event)
{
    // Do not draw invisible menu items
    if(!fMenuItem->isVisible()) return;

    QStylePainter painter(this);
    QStyleOptionMenuItem opt = getStyleOption();
    QRect boxRect;
    bool inOptionBox = false;

    QWidget *q = parentWidget();

    const int hmargin = q->style()->pixelMetric(QStyle::PM_MenuDesktopFrameWidth, 0, q),
        iconWidth = q->style()->pixelMetric(QStyle::PM_SmallIconSize, 0, q);

    if(!fMenuItem->isSeparator()) {
        if(fMenuItem->hasOptionBox()) {
            boxRect.setRect(rect().right() - hmargin - iconWidth, rect().top(), iconWidth, rect().height());
            QPoint p = QCursor::pos();
            p = mapFromGlobal(p);
            if(boxRect.contains(p)) {
                inOptionBox = true;
            } else {
                // Subtract option box rect from style option rect
                int newRight = opt.rect.right() - iconWidth - hmargin;
                opt.rect.setRight(newRight);
            }
        }
    }
    // Draw general menu item
    opt.rect.adjust(0, 0, -1, 0);
    painter.drawControl(QStyle::CE_MenuItem, opt);
    // Draw shortcut
    QKeySequence shortcutSeq = fMenuItem->shortcut();
    if(!shortcutSeq.isEmpty()) {
        // shortcut bounds
        QRect scRect = opt.rect;
        QString shortcut = shortcutSeq.toString(QKeySequence::NativeText);
        QMenu *menu = qobject_cast<QMenu *>(parentWidget());
        Q_ASSERT(menu != NULL);
        int shortcutWidth = 12;	// default value in case there is no font
        if ( menu ) {
            QFontMetrics metrics(fMenuItem->font().resolve(menu->font()));
            shortcutWidth = metrics.width(shortcut);
        }
        scRect.setLeft(scRect.right() - shortcutWidth);
        if(inOptionBox || !fMenuItem->hasOptionBox()) {
            scRect.translate(-iconWidth, 0);
        }
        scRect.translate(-kShortcutRightMargin, 0);
        painter.drawItemText(scRect, Qt::AlignRight | Qt::AlignVCenter, palette(), true, shortcut);
    }
    // Draw option box
    if(!fMenuItem->isSeparator() && fMenuItem->hasOptionBox()) {
        QIcon* boxIcon = NULL;
        QVariant v = fMenuItem->optionBoxAction()->property( "optionBoxIcon" );
        if ( v.isValid() ) {
            QString optionBoxIcon;
            optionBoxIcon = v.toString();
            boxIcon = KxQtHelper::createIcon( optionBoxIcon );
        }
        if ( boxIcon == NULL ) {
            boxIcon = new QIcon(":/optionBox.png");
        }
        boxRect.setRect(rect().right() - hmargin - iconWidth, rect().top()+(rect().height()-iconWidth)/2, iconWidth, iconWidth);
        boxIcon->paint(&painter, boxRect, Qt::AlignCenter, fMenuItem->isEnabled() ? QIcon::Normal : QIcon::Disabled);
        delete boxIcon;
    }
}