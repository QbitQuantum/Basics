void MoodBoxServer::sendPrivateMessage(Callback callback, QVariant state, qint32 recipientId, QByteArray message, QString metadata)
{
    send(callback, state, new SendPrivateMessage(recipientId, message, metadata));
}