int __PHYSFS_platformInit(void)
{
    OSErr err;
    ProcessSerialNumber psn;
    BAIL_IF_MACRO(oserr(GetCurrentProcess(&psn)) != noErr, NULL, 0);
    memset(&procInfo, '\0', sizeof (ProcessInfoRec));
    memset(&procfsspec, '\0', sizeof (FSSpec));
    procInfo.processInfoLength = sizeof (ProcessInfoRec);
    procInfo.processAppSpec = &procfsspec;
    err = GetProcessInformation(&psn, &procInfo);
    BAIL_IF_MACRO(oserr(err) != noErr, NULL, 0);
    return(1);  /* we're golden. */
} /* __PHYSFS_platformInit */