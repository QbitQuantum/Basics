}

#else  /* !defined(_M_ARM) && (defined (_CORESYS) || defined (_KERNELX)) */

static int __IsPackagedAppHelper(void)
{
    LONG retValue = APPMODEL_ERROR_NO_PACKAGE;
    UINT32 bufferLength = 0;

#if defined (_M_IX86) || defined (_M_X64)
    IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFN_GetCurrentPackageId, GetCurrentPackageId, pfn) \
    {
        retValue = pfn(&bufferLength, NULL);
    }
#else  /* defined (_M_IX86) || defined (_M_X64) */
    retValue = GetCurrentPackageId(&bufferLength, NULL);
#endif  /* defined (_M_IX86) || defined (_M_X64) */

    if (retValue == ERROR_INSUFFICIENT_BUFFER)
    {
        return 1;
    }

    /* If GetCurrentPackageId was not found, or it returned a different error,
       then this is NOT a Packaged app */
    return 0;
}
#endif  /* defined (_CORESYS) || defined (_KERNELX) */

/*******************************************************************************
*__crtIsPackagedApp() - Check if the current app is a Packaged app