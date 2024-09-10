qint64 QProcessBackend::write(const QByteArray& byteArray)
{
    return write(byteArray.data(), byteArray.length());
}