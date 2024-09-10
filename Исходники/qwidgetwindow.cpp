void QWidgetWindow::handleDragEnterMoveEvent(QDragMoveEvent *event)
{
     Q_ASSERT(event->type() ==QEvent::DragMove || !m_dragTarget);
    // Find a target widget under mouse that accepts drops (QTBUG-22987).
    QWidget *widget = m_widget->childAt(event->pos());
    if (!widget)
        widget = m_widget;
    for ( ; widget && !widget->isWindow() && !widget->acceptDrops(); widget = widget->parentWidget()) ;
    if (widget && !widget->acceptDrops())
        widget = 0;
    // Target widget unchanged: DragMove
    if (widget && widget == m_dragTarget.data()) {
        Q_ASSERT(event->type() == QEvent::DragMove);
        const QPoint mapped = widget->mapFromGlobal(m_widget->mapToGlobal(event->pos()));
        QDragMoveEvent translated(mapped, event->possibleActions(), event->mimeData(), event->mouseButtons(), event->keyboardModifiers());
        translated.setDropAction(event->dropAction());
        if (event->isAccepted()) { // Handling 'DragEnter' should suffice for the application.
            translated.accept();
            translated.setDropAction(event->dropAction());
        }
        QGuiApplication::sendSpontaneousEvent(widget, &translated);
        if (translated.isAccepted()) {
            event->accept();
        } else {
            event->ignore();
        }
        event->setDropAction(translated.dropAction());
        return;
    }
    // Target widget changed: Send DragLeave to previous, DragEnter to new if there is any
    if (m_dragTarget.data()) {
        QDragLeaveEvent le;
        QGuiApplication::sendSpontaneousEvent(m_dragTarget.data(), &le);
        m_dragTarget = 0;
    }
    if (!widget) {
         event->ignore();
         return;
    }
    m_dragTarget = widget;
    const QPoint mapped = widget->mapFromGlobal(m_widget->mapToGlobal(event->pos()));
    QDragEnterEvent translated(mapped, event->possibleActions(), event->mimeData(), event->mouseButtons(), event->keyboardModifiers());
    QGuiApplication::sendSpontaneousEvent(widget, &translated);
    if (translated.isAccepted()) {
        event->accept();
    } else {
        event->ignore();
    }
    event->setDropAction(translated.dropAction());
}