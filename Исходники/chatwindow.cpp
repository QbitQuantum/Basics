bool ChatWindow::eventFilter(QObject* sender, QEvent* event) {
    if (sender == ui->messagePlainTextEdit) {
        if (event->type() != QEvent::KeyPress) {
            return false;
        }
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
            (keyEvent->modifiers() & Qt::ShiftModifier) == 0) {
            QString messageText = ui->messagePlainTextEdit->document()->toPlainText().trimmed();
            if (!messageText.isEmpty()) {
#ifdef HAVE_QXMPP
                const QXmppMucRoom* publicChatRoom = XmppClient::getInstance().getPublicChatRoom();
                QXmppMessage message;
                message.setTo(publicChatRoom->jid());
                message.setType(QXmppMessage::GroupChat);
                message.setBody(messageText);
                XmppClient::getInstance().getXMPPClient().sendPacket(message);
#endif // HAVE_QXMPP
                QTextCursor cursor = ui->messagePlainTextEdit->textCursor();
                cursor.select(QTextCursor::Document);
                cursor.removeSelectedText();
            }
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        QVariant userVar = sender->property("user");
        if (userVar.isValid()) {
            AddressManager::getInstance().goToUser(userVar.toString());
            return true;
        }
    }
    return QWidget::eventFilter(sender, event);
}