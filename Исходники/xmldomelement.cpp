void XmlDomElement::setAttribute(const QString& name, const Length& value) noexcept
{
    setAttribute<QString>(name, value.toMmString());
}