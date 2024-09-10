int DOMString::compareString(const DOMString &other) const
{
    // Note: this strcmp does not match the semantics
    //       of the standard C strcmp.  All it needs to do is
    //       define some less than - equals - greater than ordering
    //       of strings.  How doesn't matter.
    //
    unsigned int thisLen = length();
    unsigned int otherLen = other.length();

    if (thisLen < otherLen)
        return -1;

    if (thisLen > otherLen)
        return 1;

    if (thisLen == 0)
        return 0;

    XMLCh *thisP =  this->fHandle->fDSData->fData;
    XMLCh *otherP = other.fHandle->fDSData->fData;
    unsigned int i;
    for (i=0; i<thisLen; i++)
    {
        if (thisP[i] < otherP[i])
            return -1;
        else if (thisP[i] > otherP[i])
            return 1;
    }

    return 0;
}