bool VPropertyFormWidget::eventFilter(QObject *object, QEvent *event)
{
    if (!d_ptr->UpdateEditors)
    {
        return false;
    }

    QWidget* editor = qobject_cast<QWidget*>(object);
    if (!editor)
    {
        return false;
    }

    if (event->type() == QEvent::KeyPress)
    {
        switch (static_cast<QKeyEvent *>(event)->key())
        {
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
                commitData(editor);
                event->accept();
                return true;
            default:
                return false;
        }
    }
    else if (event->type() == QEvent::FocusOut || (event->type() == QEvent::Hide && editor->isWindow()))
    {
        commitData(editor);
        return false;
    }
    else if (event->type() == QEvent::ShortcutOverride)
    {
        if (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
        {
            commitData(editor);
            event->accept();
            return true;
        }
    }
    else if (event->type() == MyCustomEventType)
    {
        commitData(editor);
        event->accept();
        return true;
    }
    else
    {
        return QGroupBox::eventFilter(object, event);
    }

    // Default:
    return false;
}