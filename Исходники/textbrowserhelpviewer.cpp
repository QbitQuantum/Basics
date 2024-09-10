bool TextBrowserHelpWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::FontChange) {
            if (!forceFont)
                return true;
        } else if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Slash) {
                keyEvent->accept();
                Core::FindPlugin::instance()->openFindToolBar(Core::FindPlugin::FindForwardDirection);
                return true;
            }
        }
    }
    return QTextBrowser::eventFilter(obj, event);
}