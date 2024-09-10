bool FancyLineEdit::event(QEvent *e) {
    // workaround for QTCREATORBUG-9453
    if (e->type() == QEvent::ShortcutOverride && completer()
            && completer()->popup() && completer()->popup()->isVisible()) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        if (ke->key() == Qt::Key_Escape && !ke->modifiers()) {
            ke->accept();
            return true;
        }
    }
    return QLineEdit::event(e);
}