/**
 * Finds the java attribute specified by
 * aAttributeName from aJad and returns the value of that attribute
 * in HBufC.
 * @param[in] aJad contents of Jad file
 * @param[in] aAttributeName the name of a java attribute
 * @return the value of the attribute. Caller gets the ownership of the
 * returned HBufC.
 * If the attribute is not found, returns NULL
 */
HBufC *CSilentMIDletInstall::ParseAttribute(const HBufC *aJad, const TDesC& aAttributeName)
{
    JELOG2(EJavaPreinstaller);

    TInt    nInd(0);
    TBool   fullNameFound(EFalse);
    TUint32 ch;

    // Start parsing from the beginning of the Jad file
    TPtrC parsePtr = aJad->Mid(nInd);

    do
    {
        // Find attribute name
        nInd = parsePtr.Find(aAttributeName);
        if (nInd < 0)
        {
            // Returns NULL if the attribute cannot be found
            return NULL;
        }

        // Check that the attribute name was preceded by line break or
        // it was at the beginning of the Jad file
        if (nInd == 0)
        {
            fullNameFound = ETrue;
        }
        else
        {
            ch = parsePtr[nInd-1];
            if ((ch == CR) || (ch == LF))
            {
                fullNameFound = ETrue;
            }
            else
            {
                // Name was just a part of longer string (not 'word match')
                fullNameFound = EFalse;
                // Skip to the last character of the found match.
                // We can skip because we are insterested only in 'word' matches
                // so the next cannot start inside the area we are skipping now.
                parsePtr.Set(parsePtr.Mid(nInd + aAttributeName.Length() - 1));
                continue;
            }
        }

        // Check whether Jad file ends after attribute name
        if (nInd + aAttributeName.Length() >= parsePtr.Length())
        {
            // Jad file ends immediately after the found
            // attribute name instance. No attribute value
            return NULL;
        }

        // Check that there is a white space character or colon after
        // attribute name
        ch = parsePtr[nInd + aAttributeName.Length()];
        if ((ch == COLON) || (ch == SP) || (ch == HT))
        {
            fullNameFound = ETrue;
        }
        else
        {
            // Name was just a part of longer string (not 'word match')
            fullNameFound = EFalse;
            // Skip to the next character after the found match
            parsePtr.Set(parsePtr.Mid(nInd + aAttributeName.Length()));
            continue;
        }
    }
    while (!fullNameFound);

    // Skip to the end of the attribute name and find ':' after the name.
    // The skipped characters must be white space chacraters, otherwise
    // the attribute name is illegal and Java Installer will not accept
    // the Jad file.
    parsePtr.Set(parsePtr.Mid(nInd + aAttributeName.Length() - 1));
    nInd = parsePtr.Locate(COLON);
    if (nInd < 0)
    {
        return NULL;
    }
    nInd++;

    // Parse attribute value (CR or LF ends)
    TInt nEndInd = parsePtr.Locate(CR);
    TInt nTmpInd = parsePtr.Locate(LF);

    if (KErrNotFound == nEndInd)
    {
        nEndInd = parsePtr.Length() - 1;
    }
    if (KErrNotFound == nTmpInd)
    {
        nTmpInd = parsePtr.Length() - 1;
    }

    if (nTmpInd < nEndInd)
    {
        nEndInd = nTmpInd;
    }

    if (nEndInd < nInd)
    {
        return NULL;
    }

    TPtrC attributeValue = parsePtr.Mid(nInd, (nEndInd - nInd));

    // Remove possible white space from the beginning and end of the value
    HBufC *bufValue = attributeValue.Alloc();
    if (NULL == bufValue)
    {
        return NULL;
    }
    TPtr value = bufValue->Des();
    value.Trim();

    return bufValue;
} // parseAttribute