bool KisInputManager::Private::EventEater::eventFilter(QObject* target, QEvent* event )
{
    if ((hungry && (event->type() == QEvent::MouseMove ||
                    event->type() == QEvent::MouseButtonPress ||
                    event->type() == QEvent::MouseButtonRelease))
        //  || (peckish && (event->type() == QEvent::MouseButtonPress))
        )
    {
        // Chow down
        if (KisTabletDebugger::instance()->debugEnabled()) {
            QString pre = QString("[BLOCKED]");
            QMouseEvent *ev = static_cast<QMouseEvent*>(event);
            dbgTablet << KisTabletDebugger::instance()->eventToString(*ev,pre);
        }
        peckish = false;
        return true;
    }
    else if ((event->type() == QEvent::MouseButtonPress) /* Need to scrutinize */ &&
             (!savedEvent)) /* Otherwise we enter a loop repeatedly storing the same event */
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        // Pocket the event and decide what to do with it later
        // savedEvent = *(static_cast<QMouseEvent*>(event));
        savedEvent = new QMouseEvent(QEvent::MouseButtonPress,
                                     mouseEvent->pos(),
                                     mouseEvent->windowPos(),
                                     mouseEvent->screenPos(),
                                     mouseEvent->button(),
                                     mouseEvent->buttons(),
                                     mouseEvent->modifiers());
        savedTarget = target;
        mouseEvent->accept();
        return true;
    }

    return false; // All clear - let this one through!
}