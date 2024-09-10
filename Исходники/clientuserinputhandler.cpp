void ClientUserInputHandler::defaultHandler(const QString &cmd, const BufferInfo &bufferInfo, const QString &text)
{
    QString command = QString("/%1 %2").arg(cmd, text);
    emit sendInput(bufferInfo, command);
}