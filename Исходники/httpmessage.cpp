void HttpMessage::setHeader(const QByteArray &name, const QByteArray &value)
{
    if (!name.isEmpty()) {
        if (!value.isNull())
            // sets the value
            m_headers[name.toUpper()] = value;
        else
            // erases the header
            m_headers.remove(name.toUpper());
    }
}