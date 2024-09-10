void HttpConnectionMap::getPersistentUriKey(const Url& url, UtlString& key)
{
    UtlString urlType;
    UtlString httpHost;
    UtlString httpPort;
    
    url.getUrlType(urlType);
    url.getHostAddress(httpHost);
    
    int tempPort = url.getHostPort();
    
    UtlString httpType = (url.getScheme() == Url::HttpsUrlScheme) ? "https" : "http";
    if (tempPort == PORT_NONE)
    {
        if (httpType == "https")
        {
            httpPort = "443";
        }
        else
        {
            httpPort = "80";
        }
    }
    else
    {
        char t[10];
        sprintf(t, "%d", tempPort);
        httpPort = t;
    }
    key = httpType + ":" + httpHost + ":" + httpPort;
    key.toLower();
}