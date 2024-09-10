bool ShortcutView::eventFilter(QObject*, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() != Qt::Key_Tab && keyEvent->key() != Qt::Key_Backtab) {
            return false;
        }
        if (!(keyEvent->modifiers() & ~Qt::ShiftModifier)) {
            m_ui.keySequenceEdit->setKeySequence(ShortcutController::keyEventToSequence(keyEvent));
            keyEvent->accept();
            return true;
        }
    }
    return false;
}