void writeCString(QDataStream &stream, QCString &str)
{
    stream.writeRawBytes(str.data(), str.length());
    stream << (Q_UINT8)0;
}