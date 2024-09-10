QDomElement KWDWriter::formatAttribute(const QDomElement &paragraph,
                                       const QString& name,
                                       const QString& attrName,
                                       const QString& attr)
{
    QDomElement lastformat = currentFormat(paragraph, true);
    QDomNodeList qdnl = lastformat.elementsByTagName(name);
    if (qdnl.length()) {
        QDomElement el;
        el = qdnl.item(0).toElement();
        el.setAttribute(attrName, attr);
        return el;
    } else {
        QDomElement al = _doc->createElement(name);
        lastformat.appendChild(al);
        al.setAttribute(attrName, attr);
        return al;
    }

}