/*! \internal
 */
QLayout::QLayout(QLayoutPrivate &dd, QLayout *lay, QWidget *w)
    : QObject(dd, lay ? static_cast<QObject*>(lay) : static_cast<QObject*>(w))
{
    Q_D(QLayout);
    if (lay) {
        lay->addItem(this);
    } else if (w) {
        if (w->layout()) {
            qWarning("QLayout: Attempting to add QLayout \"%s\" to %s \"%s\", which"
                     " already has a layout",
                     qPrintable(QObject::objectName()), w->metaObject()->className(),
                     w->objectName().toLocal8Bit().data());
            setParent(0);
        } else {
            d->topLevel = true;
            w->d_func()->layout = this;
            QT_TRY {
                invalidate();
            } QT_CATCH(...) {
                w->d_func()->layout = 0;
                QT_RETHROW;
            }
        }
    }