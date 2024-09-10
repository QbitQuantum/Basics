bool QDragManager::eventFilter(QObject *o, QEvent *e)
{
    if (beingCancelled) {
        if (e->type() == QEvent::KeyRelease && static_cast<QKeyEvent*>(e)->key() == Qt::Key_Escape) {
            qApp->removeEventFilter(this);
            Q_ASSERT(object == 0);
            beingCancelled = false;
#ifndef QT_NO_LOCALEVENTLOOP
            eventLoop->exit();
#else
            asyncDragFinished();
#endif
            return true; // block the key release
        }
        return false;
    }



    if (!o->isWidgetType())
        return false;

    switch(e->type()) {
    case QEvent::ShortcutOverride:
        // prevent accelerators from firing while dragging
        e->accept();
        return true;

    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    {
        QKeyEvent *ke = ((QKeyEvent*)e);
        if (ke->key() == Qt::Key_Escape && e->type() == QEvent::KeyPress) {
            cancel();
            qApp->removeEventFilter(this);
            beingCancelled = false;
#ifndef QT_NO_LOCALEVENTLOOP
            eventLoop->exit();
#else
            asyncDragFinished();
#endif
        } else {
            updateCursor();
        }
        return true; // Eat all key events
    }

    case QEvent::MouseButtonPress:
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

            // Fix for when we move mouse on to the deco widget
            if (qt_qws_dnd_deco && cw == qt_qws_dnd_deco)
                cw = object->target();

            while (cw && !cw->acceptDrops() && !cw->isWindow())
                cw = cw->parentWidget();

            if (object->target() != cw) {
                if (object->target()) {
                    QDragLeaveEvent dle;
                    QApplication::sendEvent(object->target(), &dle);
                    willDrop = false;
                    global_accepted_action = Qt::IgnoreAction;
                    updateCursor();
                    restoreCursor = true;
                    object->d_func()->target = 0;
                }
                if (cw && cw->acceptDrops()) {
                    object->d_func()->target = cw;
                    QDragEnterEvent dee(cw->mapFromGlobal(me->globalPos()), possible_actions, dropData,
                                        me->buttons(), me->modifiers());
                    QApplication::sendEvent(object->target(), &dee);
                    willDrop = dee.isAccepted() && dee.dropAction() != Qt::IgnoreAction;
                    global_accepted_action = willDrop ? dee.dropAction() : Qt::IgnoreAction;
                    updateCursor();
                    restoreCursor = true;
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
                updatePixmap();
                updateCursor();
            }
            if (global_accepted_action != prevAction)
                emitActionChanged(global_accepted_action);
        }
        return true; // Eat all mouse events
    }

    case QEvent::MouseButtonRelease:
    {
        qApp->removeEventFilter(this);
        if (restoreCursor) {
            willDrop = false;
#ifndef QT_NO_CURSOR
            QApplication::restoreOverrideCursor();
#endif
            restoreCursor = false;
        }
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
#ifndef QT_NO_LOCALEVENTLOOP
        eventLoop->exit();
#else
        asyncDragFinished();
#endif
        return true; // Eat all mouse events
    }

    default:
        break;
    }

    return false;
}