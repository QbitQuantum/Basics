/*!\reimp
*/
bool QLabel::event(QEvent *e)
{
    Q_D(QLabel);
    QEvent::Type type = e->type();

#ifndef QT_NO_SHORTCUT
    if (type == QEvent::Shortcut) {
        QShortcutEvent *se = static_cast<QShortcutEvent *>(e);
        if (se->shortcutId() == d->shortcutId) {
            QWidget * w = d->buddy;
            QAbstractButton *button = qobject_cast<QAbstractButton *>(w);
            if (w->focusPolicy() != Qt::NoFocus)
                w->setFocus(Qt::ShortcutFocusReason);
            if (button && !se->isAmbiguous())
                button->animateClick();
            else
                window()->setAttribute(Qt::WA_KeyboardFocusChange);
            return true;
        }
    } else
#endif
    if (type == QEvent::Resize) {
        if (d->control)
            d->textLayoutDirty = true;
    } else if (e->type() == QEvent::StyleChange
#ifdef Q_WS_MAC
               || e->type() == QEvent::MacSizeChange
#endif
               ) {
        d->setLayoutItemMargins(QStyle::SE_LabelLayoutItem);
        d->updateLabel();
    }

    return QFrame::event(e);
}