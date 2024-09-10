static bool isChildOf(QWidget* child, QWidget *parent)
{
    if (!child)
        return false;
    QObjectList list = parent->children();
    for (int i = 0; i < list.size(); ++i) {
        QObject *obj = list.at(i);
        if (!obj->isWidgetType())
            continue;
        QWidget *widget = static_cast<QWidget *>(obj);
        if (!widget->isWindow())
            continue;
        if (widget == child || isChildOf(child, widget))
            return true;
    }
    return false;
}