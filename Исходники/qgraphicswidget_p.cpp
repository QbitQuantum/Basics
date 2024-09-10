void QGraphicsWidgetPrivate::updatePalette(const QPalette &palette)
{
    Q_Q(QGraphicsWidget);
    // Update local palette setting.
    this->palette = palette;

    // Calculate new mask.
    if (q->isWindow() && !q->testAttribute(Qt::WA_WindowPropagation))
        inheritedPaletteResolveMask = 0;
    int mask = palette.resolve() | inheritedPaletteResolveMask;

    // Propagate to children.
    for (int i = 0; i < children.size(); ++i) {
        QGraphicsItem *item = children.at(i);
        if (item->isWidget()) {
            QGraphicsWidget *w = static_cast<QGraphicsWidget *>(item);
            if (!w->isWindow() || w->testAttribute(Qt::WA_WindowPropagation))
                w->d_func()->resolvePalette(mask);
        } else {
            item->d_ptr->resolvePalette(mask);
        }
    }

    // Notify change.
    QEvent event(QEvent::PaletteChange);
    QApplication::sendEvent(q, &event);
}