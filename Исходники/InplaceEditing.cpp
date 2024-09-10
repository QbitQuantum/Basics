void onInplaceWidgetDestroyed(QObject* object)
{
    // set focus to parent of inplace widget
    QWidget* parent = qobject_cast<QWidget*>(object->parent());
    if (parent)
        parent->setFocus();
}