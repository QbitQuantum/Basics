void HttpRequestContext::extractPostCgiVariables(const HttpBody& body)
{
    int length;
    UtlString bodyBytes;

    body.getBytes(&bodyBytes, &length);
    parseCgiVariables(bodyBytes.data());
    bodyBytes.remove(0);
}