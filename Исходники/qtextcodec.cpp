/*!
    \overload

    Converts the bytes in the byte array specified by \a ba to Unicode
    and returns the result.
*/
QString QTextDecoder::toUnicode(const QByteArray &ba)
{
    return c->toUnicode(ba.constData(), ba.length(), &state);
}