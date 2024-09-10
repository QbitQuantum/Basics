// Pseudo factory
HttpBody* HttpBody::createBody(const char* bodyBytes_,
                               ssize_t bodyLength,
                               const char* contentType,
                               const char* contentEncoding)
{
    UtlString buff(bodyBytes_, bodyLength);
    const char* bodyBytes = buff.data();
    
    HttpBody* body = NULL;

    UtlString contentTypeString;
    if(contentType)
    {
        contentTypeString.append(contentType);
        contentTypeString.toLower();
    }
    if(contentType &&
       strcmp(contentTypeString.data(), SDP_CONTENT_TYPE) == 0)
    {
        body = new SdpBody(bodyBytes, bodyLength);
    }
    else if(contentType &&
            strcmp(contentTypeString.data(), CONTENT_SMIME_PKCS7) == 0)
    {
        body = new SmimeBody(bodyBytes, bodyLength, contentEncoding);
    }
    else if ((bodyLength  > 1) ||
             (bodyBytes[0] != '\n'))
    {
        body = new HttpBody(bodyBytes, bodyLength,
                            contentType);
    }

    return(body);
}