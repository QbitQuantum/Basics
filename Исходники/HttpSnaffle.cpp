bool HttpSnaffle::StartFetch(std::string objectPath)
{
    // Under Win95/HTTP1.0 you need an initial slash
    if (objectPath[0] != '/')
        objectPath = std::string("/") + objectPath;

    // NB: If you consider setting INTERNET_FLAG_PRAGMA_NOCACHE, be
    // warned it doesn't work on a base Win95 machine.

    myRequest = HttpOpenRequestA(myServerConnection, NULL, objectPath.c_str(), NULL, NULL, 
                                 NULL, // mime types
                                 // Force a load from the server, not the cache.  This is in case
                                 // the file has changed, or has been corrupted during previous transfer.
                                 INTERNET_FLAG_RELOAD | INTERNET_FLAG_RESYNCHRONIZE, 
                                 myContext);

    if (myRequest == NULL)
        return false;

    BOOL result = HttpSendRequest(myRequest, 0, 0, 0, 0);
    if (!result)
        return false;

    return true;
}