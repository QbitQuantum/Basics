QDesignerFormWindowInterface *QDesignerFormWindowInterface::findFormWindow(QObject *object)
{
    while (object != 0) {
        if (QDesignerFormWindowInterface *fw = qobject_cast<QDesignerFormWindowInterface*>(object)) {
            return fw;
        } else {
            QWidget *w = qobject_cast<QWidget *>(object);
            // QDesignerMenu is a window, so stopFindAtTopLevel(w) returns 0.
            // However, we want to find the form window for QActions of a menu.
            // If this check is inside stopFindAtTopLevel(w), it will break designer
            // menu editing (e.g. when clicking on items inside an opened menu)
            if (w && w->isWindow() && stopFindAtTopLevel(w, false))
                break;

        }

        object = object->parent();
    }

    return 0;
}