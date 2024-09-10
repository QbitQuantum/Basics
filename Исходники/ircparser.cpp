QByteArray IrcParser::decrypt(Network *network, const QString &bufferName, const QByteArray &message, bool isTopic)
{
#ifdef HAVE_QCA2
    if (message.isEmpty())
        return message;

    if (!Cipher::neededFeaturesAvailable())
        return message;

    Cipher *cipher = qobject_cast<CoreNetwork *>(network)->cipher(bufferName);
    if (!cipher || cipher->key().isEmpty())
        return message;

    return isTopic ? cipher->decryptTopic(message) : cipher->decrypt(message);
#else
    Q_UNUSED(network);
    Q_UNUSED(bufferName);
    Q_UNUSED(isTopic);
    return message;
#endif
}