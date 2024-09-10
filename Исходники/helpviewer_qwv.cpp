qint64 HelpNetworkReply::readData(char *buffer, qint64 maxlen)
{
    qint64 len = qMin(qint64(data.length()), maxlen);
    if (len) {
        std::memcpy(buffer, data.constData(), len);
        data.remove(0, len);
    }
    return len;
}