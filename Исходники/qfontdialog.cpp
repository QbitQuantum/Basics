bool QFontDialog::eventFilter(QObject *o , QEvent *e)
{
    Q_D(QFontDialog);
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *k = (QKeyEvent *)e;
        if (o == d->sizeEdit &&
                (k->key() == Qt::Key_Up ||
                 k->key() == Qt::Key_Down ||
                 k->key() == Qt::Key_PageUp ||
                 k->key() == Qt::Key_PageDown)) {

            int ci = d->sizeList->currentItem();
            (void)QApplication::sendEvent(d->sizeList, k);

            if (ci != d->sizeList->currentItem()
                    && style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this))
                d->sizeEdit->selectAll();
            return true;
        } else if ((o == d->familyList || o == d->styleList) &&
                   (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)) {
            k->accept();
            accept();
            return true;
        }
    } else if (e->type() == QEvent::FocusIn
               && style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, this)) {
        if (o == d->familyList)
            d->familyEdit->selectAll();
        else if (o == d->styleList)
            d->styleEdit->selectAll();
        else if (o == d->sizeList)
            d->sizeEdit->selectAll();
    } else if (e->type() == QEvent::MouseButtonPress && o == d->sizeList) {
        d->sizeEdit->setFocus();
    }
    return QDialog::eventFilter(o, e);
}