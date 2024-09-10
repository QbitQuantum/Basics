bool QToolBoxHelper::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::ChildPolished:
        // Install on the buttons
        if (watched == m_toolbox) {
            QChildEvent *ce = static_cast<QChildEvent *>(event);
            if (!qstrcmp(ce->child()->metaObject()->className(), "QToolBoxButton"))
                ce->child()->installEventFilter(this);
        }
        break;
    case QEvent::ContextMenu:
        if (watched != m_toolbox) {
            // An action invoked from the passive interactor (ToolBox button) might
            // cause its deletion within its event handler, triggering a warning. Re-post
            // the event to the toolbox.
            QContextMenuEvent *current = static_cast<QContextMenuEvent *>(event);
            QContextMenuEvent *copy = new QContextMenuEvent(current->reason(), current->pos(), current-> globalPos(), current->modifiers());
            QApplication::postEvent(m_toolbox, copy);
            current->accept();
            return true;
        }
        break;
    case QEvent::MouseButtonRelease:
        if (watched != m_toolbox)
            if (QDesignerFormWindowInterface *fw = QDesignerFormWindowInterface::findFormWindow(m_toolbox)) {
                fw->clearSelection();
                fw->selectWidget(m_toolbox, true);
            }
        break;
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}