ECode CQName::ValueOf(
    /* [in] */ String qNameAsString,
    /* [out] */  IQName** qName)
{
    // null is not valid
    if (qNameAsString == NULL) {
        // throw new IllegalArgumentException("cannot create QName from \"null\" or \"\" String");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    // "" local part is valid to preserve compatible behavior with QName 1.0
    if (qNameAsString.GetLength() == 0) {
        return CQName::New(
            IXMLConstants::NULL_NS_URI,
            qNameAsString,
            IXMLConstants::DEFAULT_NS_PREFIX,
            qName);
    }

    // local part only?
    if (qNameAsString.GetChar(0) != '{') {
        return CQName::New(
            IXMLConstants::NULL_NS_URI,
            qNameAsString,
            IXMLConstants::DEFAULT_NS_PREFIX,
            qName);
    }

    // Namespace URI improperly specified?
    if (qNameAsString.StartWith(String("{") + IXMLConstants::NULL_NS_URI + "}")) {
        // throw new IllegalArgumentException(
        //     "Namespace URI .equals(XMLConstants.NULL_NS_URI), "
        //     + ".equals(\"" + XMLConstants.NULL_NS_URI + "\"), "
        //     + "only the local part, "
        //     + "\"" + qNameAsString.substring(2 + XMLConstants.NULL_NS_URI.length()) + "\", "
        //     + "should be provided.");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    // Namespace URI and local part specified
    Int32 endOfNamespaceURI = qNameAsString.IndexOf('}');
    if (endOfNamespaceURI == -1) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
        // throw new IllegalArgumentException(
        //     "cannot create QName from \""
        //         + qNameAsString
        //         + "\", missing closing \"}\"");
    }
    return CQName::New(
        qNameAsString.Substring(1, endOfNamespaceURI),
        qNameAsString.Substring(endOfNamespaceURI + 1),
        IXMLConstants::DEFAULT_NS_PREFIX,
        qName);
}