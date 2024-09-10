bool MythTerminalKeyFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *e = (QKeyEvent*)(event);
        QStringList actions;
        bool handled = GetMythMainWindow()->TranslateKeyPress("qt", e, actions,
                                                              false);
        if (!handled && !actions.isEmpty())
        {
            if (actions.contains("LEFT") || actions.contains("RIGHT") ||
                actions.contains("UP") || actions.contains("DOWN") ||
                actions.contains("ESCAPE"))
            {
                return QObject::eventFilter(obj, event);
            }
            else
            {
                emit KeyPressd(e);
                e->accept();
                return true;
            }
        }
        else
        {
            emit KeyPressd(e);
            e->accept();
            return true;
        }
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}