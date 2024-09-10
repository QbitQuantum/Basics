// ---------------------------------------------------------------------------
//  Implementation of the virtual message loader API
// ---------------------------------------------------------------------------
bool ICUMsgLoader::loadMsg( const   XMLMsgLoader::XMLMsgId  msgToLoad
                          ,         XMLCh* const            toFill
                          , const   XMLSize_t               maxChars)
{
    UErrorCode   err = U_ZERO_ERROR;
    int32_t      strLen = 0;

    // Assuming array format
    const UChar *name = ures_getStringByIndex(fDomainBundle, (int32_t)msgToLoad-1, &strLen, &err);

    if (!U_SUCCESS(err) || (name == NULL))
    {
        return false;
    }

    int retStrLen = strLen > (int32_t)maxChars ? maxChars : strLen;

    if (sizeof(UChar)==sizeof(XMLCh))
    {
        XMLString::moveChars(toFill, (XMLCh*)name, retStrLen);
        toFill[retStrLen] = (XMLCh) 0;
    }
    else
    {
        XMLCh* retStr = toFill;
        const UChar *srcPtr = name;

        while (retStrLen--)
           *retStr++ = *srcPtr++;

        *retStr = 0;
    }

    return true;
}