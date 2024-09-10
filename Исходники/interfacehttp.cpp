void InterfaceHttp::webSocketsProcessMessage(const QString &message) {
    WebSocket *webSocket = qobject_cast<WebSocket *>(sender());
    if(webSocket) {
        QStringList commandItems = message.split(COMMAND_END, QString::SkipEmptyParts);;
        QString response;
        foreach(const QString & command, commandItems)
            response += MessageManager::incomingMessage(MessageIncomming("http", webSocket->peerAddress().toString(), webSocket->peerPort(), "", command, command.split(" ", QString::SkipEmptyParts)), true, (command != "goto"));
        if(!response.isEmpty())
            webSocket->send(response);
    }
}