DMAD_EXPORT_C TPtrC8 TDmAdUtil::FirstUriSeg(const TDesC8& aUri)
    {
    TInt i;
    TBool found = EFalse;
    for (i=0; i<aUri.Length(); i++)
        {
        if (aUri[i] == '/')
            {
            found = ETrue;
            break;
            }
        }
    if (found)
        {
        return aUri.Left(i);
        }
    else
        {
        return aUri;
        }
    }