QList<QWidget*> childWidgets(const QWidget *widget)
{
    if (widget == 0)
        return QList<QWidget*>();
    QList<QObject*> list = widget->children();
    QList<QWidget*> widgets;
    for (int i = 0; i < list.size(); ++i) {
        QWidget *w = qobject_cast<QWidget *>(list.at(i));
        if (!w)
            continue;
        QString objectName = w->objectName();
        if (!w->isWindow()
              && !qobject_cast<QFocusFrame*>(w)
              && !qobject_cast<QMenu*>(w)
              && objectName != QLatin1String("qt_rubberband")
              && objectName != QLatin1String("qt_qmainwindow_extended_splitter")) {
            widgets.append(w);
        }
    }
    return widgets;
}