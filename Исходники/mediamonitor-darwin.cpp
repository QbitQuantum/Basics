/**
 * Given a BSD device node name, guess its media type
 */
MythMediaType MediaTypeForBSDName(const char *bsdName)
{
    CFMutableDictionaryRef  matchingDict;
    kern_return_t           kernResult;
    io_iterator_t           iter;
    io_service_t            service;
    QString                 msg = QString("MediaTypeForBSDName(%1)")
                                  .arg(bsdName);
    MythMediaType           mediaType;


    if (!bsdName || !*bsdName)
    {
        LOG(VB_GENERAL, LOG_ALERT, msg + " - No name supplied?");
        return MEDIATYPE_UNKNOWN;
    }

    matchingDict = IOBSDNameMatching(sMasterPort, 0, bsdName);
    if (!matchingDict)
    {
        LOG(VB_GENERAL, LOG_ALERT, 
                 msg + " - IOBSDNameMatching() returned a NULL dictionary.");
        return MEDIATYPE_UNKNOWN;
    }

    // Return an iterator across all objects with the matching
    // BSD node name. Note that there should only be one match!
    kernResult = IOServiceGetMatchingServices(sMasterPort, matchingDict, &iter);

    if (KERN_SUCCESS != kernResult)
    {
        LOG(VB_GENERAL, LOG_ALERT,
                 QString(msg + " - IOServiceGetMatchingServices() returned %2")
                         .arg(kernResult));
        return MEDIATYPE_UNKNOWN;
    }
    if (!iter)
    {
        LOG(VB_GENERAL, LOG_ALERT,
                 msg + " - IOServiceGetMatchingServices() returned a NULL "
                       "iterator");
        return MEDIATYPE_UNKNOWN;
    }

    service = IOIteratorNext(iter);

    // Release this now because we only expect
    // the iterator to contain a single io_service_t.
    IOObjectRelease(iter);

    if (!service)
    {
        LOG(VB_GENERAL, LOG_ALERT, 
                 msg + " - IOIteratorNext() returned a NULL iterator");
        return MEDIATYPE_UNKNOWN;
    }
    mediaType = FindMediaType(service);
    IOObjectRelease(service);
    return mediaType;
}