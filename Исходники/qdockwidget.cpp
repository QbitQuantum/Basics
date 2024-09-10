void QDockWidgetPrivate::nonClientAreaMouseEvent(QMouseEvent *event)
{
    Q_Q(QDockWidget);

    int fw = q->style()->pixelMetric(QStyle::PM_DockWidgetFrameWidth, 0, q);

    QRect geo = q->geometry();
    QRect titleRect = q->frameGeometry();
#ifdef Q_WS_MAC
    if ((features & QDockWidget::DockWidgetVerticalTitleBar)) {
        titleRect.setTop(geo.top());
        titleRect.setBottom(geo.bottom());
        titleRect.setRight(geo.left() - 1);
    } else
#endif
    {
        titleRect.setLeft(geo.left());
        titleRect.setRight(geo.right());
        titleRect.setBottom(geo.top() - 1);
        titleRect.adjust(0, fw, 0, 0);
    }

    switch (event->type()) {
        case QEvent::NonClientAreaMouseButtonPress:
            if (!titleRect.contains(event->globalPos()))
                break;
            if (state != 0)
                break;
            if (qobject_cast<QMainWindow*>(parent) == 0)
                break;
            if (isAnimating())
                break;
            initDrag(event->pos(), true);
            if (state == 0)
                break;
#ifdef Q_WS_WIN
            // On Windows, NCA mouse events don't contain modifier info
            state->ctrlDrag = GetKeyState(VK_CONTROL) & 0x8000;
#else
            state->ctrlDrag = event->modifiers() & Qt::ControlModifier;
#endif
            startDrag();
            break;
        case QEvent::NonClientAreaMouseMove:
            if (state == 0 || !state->dragging)
                break;

#ifndef Q_OS_MAC
            if (state->nca) {
                endDrag();
            }
#endif
            break;
        case QEvent::NonClientAreaMouseButtonRelease:
#ifdef Q_OS_MAC
                        if (state)
                                endDrag();
#endif
                        break;
        case QEvent::NonClientAreaMouseButtonDblClick:
            _q_toggleTopLevel();
            break;
        default:
            break;
    }
}