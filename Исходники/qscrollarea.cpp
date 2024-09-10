/*!
    Removes the scroll area's widget, and passes ownership of the
    widget to the caller.

    \sa widget()
 */
QWidget *QScrollArea::takeWidget()
{
    Q_D(QScrollArea);
    QWidget *w = d->widget;
    d->widget = 0;
    if (w)
        w->setParent(0);
    return w;
}