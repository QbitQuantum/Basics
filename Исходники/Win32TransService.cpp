int _wcsnicmp(LPCWSTR comp1, LPCWSTR comp2, unsigned int nLen)
{
    unsigned int len = XMLString::stringLen( comp1);
    unsigned int otherLen = XMLString::stringLen( comp2);
    unsigned int countChar = 0;
    unsigned int maxChars;
    int          theResult = 0;

    // Determine at what string index the comparison stops.
    len = ( len > nLen ) ? nLen : len;
    otherLen = ( otherLen > nLen ) ? nLen : otherLen;
    maxChars = ( len > otherLen ) ? otherLen : len;

    // Handle situation when one argument or the other is NULL
    // by returning +/- string length of non-NULL argument (inferred
    // from XMLString::CompareNString).

    // Obs. Definition of stringLen(XMLCh*) implies NULL ptr and ptr
    // to Empty String are equivalent.  It handles NULL args, BTW.

    if ( !comp1 )
    {
        // Negative because null ptr (c1) less than string (c2).
        return ( 0 - otherLen );
    }

    if ( !comp2 )
    {
        // Positive because string (c1) still greater than null ptr (c2).
        return len;
    }

    // Copy const parameter strings (plus terminating nul) into locals.
    XMLCh* firstBuf = (XMLCh*) XMLPlatformUtils::fgMemoryManager->allocate( (++len) * sizeof(XMLCh) );//new XMLCh[ ++len];
    XMLCh* secondBuf = (XMLCh*) XMLPlatformUtils::fgMemoryManager->allocate( (++otherLen) * sizeof(XMLCh) );//new XMLCh[ ++otherLen];
    memcpy( firstBuf, comp1, len * sizeof(XMLCh));
    memcpy( secondBuf, comp2, otherLen * sizeof(XMLCh));

    // Then uppercase both strings, losing their case info.
    ::LCMapStringW( GetThreadLocale(), LCMAP_UPPERCASE, (LPWSTR)firstBuf, len, (LPWSTR)firstBuf, len);
    ::LCMapStringW( GetThreadLocale(), LCMAP_UPPERCASE, (LPWSTR)secondBuf, otherLen, (LPWSTR)secondBuf, otherLen);

    // Strings are equal until proven otherwise.
    while ( ( countChar < maxChars ) && ( !theResult ) )
    {
        theResult = (int)(firstBuf[countChar]) - (int)(secondBuf[countChar]);
        ++countChar;
    }

    XMLPlatformUtils::fgMemoryManager->deallocate(firstBuf);//delete [] firstBuf;
    XMLPlatformUtils::fgMemoryManager->deallocate(secondBuf);//delete [] secondBuf;

    return theResult;
}