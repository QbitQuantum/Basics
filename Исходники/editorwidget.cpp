bool EditorWidgetKate::eventFilter(QObject *, QEvent *ev)
{
    switch(ev->type())
    {
        case QEvent::ShortcutOverride:
        {
            QKeyEvent *kev = (QKeyEvent*)ev;
            if(kev->key() == Qt::Key_F5)
            {
                kev->accept();
                emit applyShortcutPressed();
                return true;
            }
            break;
        }
        default: break;
    }
    return false;
}