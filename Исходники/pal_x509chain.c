static void MergeStatusCodes(CFTypeRef key, CFTypeRef value, void* context)
{
    // Windows (and therefore .NET) certificate status codes are defined on an int32_t.
    // The top 32 bits will be used to convey error information, the bottom 32 bits
    // as a data aggregator for the status codes.
    uint64_t* pStatus = (uint64_t*)context;

    if (key == NULL)
    {
        return;
    }

    // If any error code was already set.
    if (*pStatus > INT_MAX)
    {
        return;
    }

    if (CFGetTypeID(key) != CFStringGetTypeID())
    {
        *pStatus |= PAL_X509ChainErrorUnknownValueType;
        return;
    }

    (void)value;
    CFStringRef keyString = (CFStringRef)key;

    if (CFEqual(keyString, CFSTR("NotValidBefore")) || CFEqual(keyString, CFSTR("ValidLeaf")) ||
        CFEqual(keyString, CFSTR("ValidIntermediates")) || CFEqual(keyString, CFSTR("ValidRoot")) ||
        CFEqual(keyString, CFSTR("TemporalValidity")))
        *pStatus |= PAL_X509ChainNotTimeValid;
    else if (CFEqual(keyString, CFSTR("Revocation")))
        *pStatus |= PAL_X509ChainRevoked;
    else if (CFEqual(keyString, CFSTR("KeyUsage")))
        *pStatus |= PAL_X509ChainNotValidForUsage;
    else if (CFEqual(keyString, CFSTR("AnchorTrusted")))
        *pStatus |= PAL_X509ChainUntrustedRoot;
    else if (CFEqual(keyString, CFSTR("BasicConstraints")))
        *pStatus |= PAL_X509ChainInvalidBasicConstraints;
    else if (CFEqual(keyString, CFSTR("UsageConstraints")))
        *pStatus |= PAL_X509ChainExplicitDistrust;
    else if (CFEqual(keyString, CFSTR("RevocationResponseRequired")))
        *pStatus |= PAL_X509ChainRevocationStatusUnknown;
    else if (CFEqual(keyString, CFSTR("MissingIntermediate")))
        *pStatus |= PAL_X509ChainPartialChain;
    else if (CFEqual(keyString, CFSTR("WeakLeaf")) || CFEqual(keyString, CFSTR("WeakIntermediates")) ||
             CFEqual(keyString, CFSTR("WeakRoot")) || CFEqual(keyString, CFSTR("WeakKeySize")))
    {
        // Because we won't report this out of a chain built by .NET on Windows,
        // don't report it here.
        //
        // (On Windows CERT_CHAIN_PARA.pStrongSignPara is NULL, so "strongness" checks
        // are not performed).
    }
    else if (CFEqual(keyString, CFSTR("StatusCodes")))
    {
        // 10.13 added a StatusCodes value which may be a numeric rehashing of the string data.
        // It doesn't represent a new error code, and we're still getting the old ones, so
        // just ignore it for now.
    }
    else if (CFEqual(keyString, CFSTR("NonEmptySubject")))
    {
        // Not a "problem" that we report.
    }
    else
    {
#ifdef DEBUGGING_UNKNOWN_VALUE
        printf("%s\n", CFStringGetCStringPtr(keyString, CFStringGetSystemEncoding()));
#endif
        *pStatus |= PAL_X509ChainErrorUnknownValue;
    }
}