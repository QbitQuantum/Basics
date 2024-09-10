bool QDragManager::eventFilter(QObject *o, QEvent *e)
{
 if (beingCancelled) {
        return false;
    }
    if (!o->isWidgetType())
        return false;

    switch(e->type()) {
        case QEvent::MouseButtonPress:
        {
        }
        case QEvent::MouseMove:
        {
            if (!object) { //#### this should not happen
                qWarning("QDragManager::eventFilter: No object");
                return true;
            }
            QDragManager *manager = QDragManager::self();
            QMimeData *dropData = manager->object ? manager->dragPrivate()->data : manager->dropData;
            if (manager->object)
                possible_actions =  manager->dragPrivate()->possible_actions;
            else
                possible_actions = Qt::IgnoreAction;

            QMouseEvent *me = (QMouseEvent *)e;

            if (me->buttons()) {
                Qt::DropAction prevAction = global_accepted_action;
                QWidget *cw = QApplication::widgetAt(me->globalPos());
                // map the Coords relative to the window.
                if (!cw)
                    return true;

                while (cw && !cw->acceptDrops() && !cw->isWindow())
                    cw = cw->parentWidget();

                bool oldWillDrop = willDrop;
                if (object->target() != cw) {
                    if (object->target()) {
                        QDragLeaveEvent dle;
                        QApplication::sendEvent(object->target(), &dle);
                        willDrop = false;
                        global_accepted_action = Qt::IgnoreAction;
                        if (oldWillDrop != willDrop)
                            updateCursor();
                        object->d_func()->target = 0;
                    }
                    if (cw && cw->acceptDrops()) {
                        object->d_func()->target = cw;
                        QDragEnterEvent dee(cw->mapFromGlobal(me->globalPos()), possible_actions, dropData,
                                            me->buttons(), me->modifiers());
                        QApplication::sendEvent(object->target(), &dee);
                        willDrop = dee.isAccepted() && dee.dropAction() != Qt::IgnoreAction;
                        global_accepted_action = willDrop ? dee.dropAction() : Qt::IgnoreAction;
                        if (oldWillDrop != willDrop)
                            updateCursor();
                    }
                } else if (cw) {
                    QDragMoveEvent dme(cw->mapFromGlobal(me->globalPos()), possible_actions, dropData,
                                       me->buttons(), me->modifiers());
                    if (global_accepted_action != Qt::IgnoreAction) {
                        dme.setDropAction(global_accepted_action);
                        dme.accept();
                    }
                    QApplication::sendEvent(cw, &dme);
                    willDrop = dme.isAccepted();
                    global_accepted_action = willDrop ? dme.dropAction() : Qt::IgnoreAction;
                    if (oldWillDrop != willDrop) {
                        updatePixmap();
                        updateCursor();
                    }
                }
                if (global_accepted_action != prevAction)
                    emitActionChanged(global_accepted_action);
            }
            return true; // Eat all mouse events
        }

        case QEvent::MouseButtonRelease:
        {
            qApp->removeEventFilter(this);
#ifndef QT_NO_CURSOR
            if (restoreCursor) {
                QApplication::restoreOverrideCursor();
                willDrop = false;
                restoreCursor = false;
            }
#endif
            if (object && object->target()) {

                QMouseEvent *me = (QMouseEvent *)e;

                QDragManager *manager = QDragManager::self();
                QMimeData *dropData = manager->object ? manager->dragPrivate()->data : manager->dropData;

                QDropEvent de(object->target()->mapFromGlobal(me->globalPos()), possible_actions, dropData,
                              me->buttons(), me->modifiers());
                QApplication::sendEvent(object->target(), &de);
                if (de.isAccepted())
                    global_accepted_action = de.dropAction();
                else
                    global_accepted_action = Qt::IgnoreAction;

                if (object)
                    object->deleteLater();
                drag_object = object = 0;
            }
            eventLoop->exit();
            return true; // Eat all mouse events
        }

        default:
             break;
    }
    return false;
}