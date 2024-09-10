static bool verifyCustomHandlerURL(const String& baseURL, const String& url, ExceptionCode& ec)
{
    // The specification requires that it is a SYNTAX_ERR if the "%s" token is
    // not present.
    static const char token[] = "%s";
    int index = url.find(token);
    if (-1 == index) {
        ec = SYNTAX_ERR;
        return false;
    }

    // It is also a SYNTAX_ERR if the custom handler URL, as created by removing
    // the "%s" token and prepending the base url, does not resolve.
    String newURL = url;
    newURL.remove(index, WTF_ARRAY_LENGTH(token) - 1);

    URL base(ParsedURLString, baseURL);
    URL kurl(base, newURL);

    if (kurl.isEmpty() || !kurl.isValid()) {
        ec = SYNTAX_ERR;
        return false;
    }

    return true;
}