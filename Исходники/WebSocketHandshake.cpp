// https://tools.ietf.org/html/rfc6455#section-4.1
// "The HTTP version MUST be at least 1.1."
static inline bool headerHasValidHTTPVersion(StringView httpStatusLine)
{
    const char* httpVersionStaticPreambleLiteral = "HTTP/";
    StringView httpVersionStaticPreamble(reinterpret_cast<const LChar*>(httpVersionStaticPreambleLiteral), strlen(httpVersionStaticPreambleLiteral));
    if (!httpStatusLine.startsWith(httpVersionStaticPreamble))
        return false;

    // Check that there is a version number which should be at least three characters after "HTTP/"
    unsigned preambleLength = httpVersionStaticPreamble.length();
    if (httpStatusLine.length() < preambleLength + 3)
        return false;

    auto dotPosition = httpStatusLine.find('.', preambleLength);
    if (dotPosition == notFound)
        return false;

    StringView majorVersionView = httpStatusLine.substring(preambleLength, dotPosition - preambleLength);
    bool isValid;
    int majorVersion = majorVersionView.toIntStrict(isValid);
    if (!isValid)
        return false;

    unsigned minorVersionLength;
    unsigned charactersLeftAfterDotPosition = httpStatusLine.length() - dotPosition;
    for (minorVersionLength = 1; minorVersionLength < charactersLeftAfterDotPosition; minorVersionLength++) {
        if (!isASCIIDigit(httpStatusLine[dotPosition + minorVersionLength]))
            break;
    }
    int minorVersion = (httpStatusLine.substring(dotPosition + 1, minorVersionLength)).toIntStrict(isValid);
    if (!isValid)
        return false;

    return (majorVersion >= 1 && minorVersion >= 1) || majorVersion >= 2;
}