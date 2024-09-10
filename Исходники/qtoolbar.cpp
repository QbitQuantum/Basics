/*! \reimp */
bool QToolBar::event(QEvent *event)
{
    Q_D(QToolBar);

    switch (event->type()) {
    case QEvent::Timer:
        if (d->waitForPopupTimer.timerId() == static_cast<QTimerEvent*>(event)->timerId()) {
            QWidget *w = QApplication::activePopupWidget();
            if (!waitForPopup(this, w)) {
                d->waitForPopupTimer.stop();
                if (!this->underMouse())
                    d->layout->setExpanded(false);
            }
        }
        break;
    case QEvent::Hide:
        if (!isHidden())
            break;
    // fallthrough intended
    case QEvent::Show:
        d->toggleViewAction->setChecked(event->type() == QEvent::Show);
        emit visibilityChanged(event->type() == QEvent::Show);
#if defined(Q_WS_MAC)
        if (toolbarInUnifiedToolBar(this)) {
            // I can static_cast because I did the qobject_cast in the if above, therefore
            // we must have a QMainWindowLayout here.
            QMainWindowLayout *mwLayout = qt_mainwindow_layout(qobject_cast<QMainWindow *>(parentWidget()));
            mwLayout->fixSizeInUnifiedToolbar(this);
            mwLayout->syncUnifiedToolbarVisibility();
        }
#endif // Q_WS_MAC
        break;
    case QEvent::ParentChange:
        d->layout->checkUsePopupMenu();
#if defined(Q_WS_MAC)
        if (parentWidget() && parentWidget()->isWindow())
            qt_mac_updateToolBarButtonHint(parentWidget());
#endif
        break;

    case QEvent::MouseButtonPress: {
        if (d->mousePressEvent(static_cast<QMouseEvent*>(event)))
            return true;
        break;
    }
    case QEvent::MouseButtonRelease:
        if (d->mouseReleaseEvent(static_cast<QMouseEvent*>(event)))
            return true;
        break;
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
        // there's nothing special to do here and we don't want to update the whole widget
        return true;
    case QEvent::HoverMove: {
#ifndef QT_NO_CURSOR
        QHoverEvent *e = static_cast<QHoverEvent*>(event);
        QStyleOptionToolBar opt;
        initStyleOption(&opt);
        if (style()->subElementRect(QStyle::SE_ToolBarHandle, &opt, this).contains(e->pos()))
            setCursor(Qt::SizeAllCursor);
        else
            unsetCursor();
#endif
        break;
    }
    case QEvent::MouseMove:
        if (d->mouseMoveEvent(static_cast<QMouseEvent*>(event)))
            return true;
        break;
#ifdef Q_OS_WINCE
    case QEvent::ContextMenu:
    {
        QContextMenuEvent* contextMenuEvent = static_cast<QContextMenuEvent*>(event);
        QWidget* child = childAt(contextMenuEvent->pos());
        QAbstractButton* button = qobject_cast<QAbstractButton*>(child);
        if (button)
            button->setDown(false);
    }
    break;
#endif
    case QEvent::Leave:
        if (d->state != 0 && d->state->dragging) {
#ifdef Q_OS_WIN
            // This is a workaround for loosing the mouse on Vista.
            QPoint pos = QCursor::pos();
            QMouseEvent fake(QEvent::MouseMove, mapFromGlobal(pos), pos, Qt::NoButton,
                             QApplication::mouseButtons(), QApplication::keyboardModifiers());
            d->mouseMoveEvent(&fake);
#endif
        } else {
            if (!d->layout->expanded)
                break;

            QWidget *w = QApplication::activePopupWidget();
            if (waitForPopup(this, w)) {
                d->waitForPopupTimer.start(POPUP_TIMER_INTERVAL, this);
                break;
            }

            d->waitForPopupTimer.stop();
            d->layout->setExpanded(false);
            break;
        }
    default:
        break;
    }
    return QWidget::event(event);
}