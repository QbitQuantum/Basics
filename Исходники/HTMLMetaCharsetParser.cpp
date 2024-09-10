TextEncoding HTMLMetaCharsetParser::encodingFromMetaAttributes(const AttributeList& attributes)
{
    bool gotPragma = false;
    enum { None, Charset, Pragma } mode = None;
    StringView charset;

    for (auto& attribute : attributes) {
        const String& attributeName = attribute.first;
        const String& attributeValue = attribute.second;

        if (attributeName == http_equivAttr) {
            if (equalIgnoringCase(attributeValue, "content-type"))
                gotPragma = true;
        } else if (charset.isEmpty()) {
            if (attributeName == charsetAttr) {
                charset = attributeValue;
                mode = Charset;
            } else if (attributeName == contentAttr) {
                charset = extractCharset(attributeValue);
                if (charset.length())
                    mode = Pragma;
            }
        }
    }

    if (mode == Charset || (mode == Pragma && gotPragma))
        return TextEncoding(stripLeadingAndTrailingHTMLSpaces(charset.toStringWithoutCopying()));

    return TextEncoding();
}