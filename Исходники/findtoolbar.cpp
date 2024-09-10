bool FindToolBar::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Down) {
            if (obj == m_ui.findEdit) {
                if (m_ui.findEdit->text().isEmpty())
                    m_findCompleter->setCompletionPrefix(QString());
                m_findCompleter->complete();
            } else if (obj == m_ui.replaceEdit) {
                if (m_ui.replaceEdit->text().isEmpty())
                    m_replaceCompleter->setCompletionPrefix(QString());
                m_replaceCompleter->complete();
            }
        }
    }

    if ((obj == m_ui.findEdit || obj == m_findCompleter->popup())
               && event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Space && (ke->modifiers() & Utils::HostOsInfo::controlModifier())) {
            QString completedText = m_currentDocumentFind->completedFindString();
            if (!completedText.isEmpty()) {
                setFindText(completedText);
                ke->accept();
                return true;
            }
        }
    } else if (obj == this && event->type() == QEvent::ShortcutOverride) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Space && (ke->modifiers() & Utils::HostOsInfo::controlModifier())) {
            event->accept();
            return true;
        }
    } else if (obj == this && event->type() == QEvent::Hide) {
        invokeClearResults();
        if (m_currentDocumentFind->isEnabled())
            m_currentDocumentFind->clearFindScope();
    }
    return Utils::StyledBar::eventFilter(obj, event);
}