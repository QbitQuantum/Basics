SOM_Scope void  SOMLINK ODLinkSpecGetOriginatingProcessID(ODLinkSpec *somSelf, Environment *ev,
                ProcessSerialNumber *psn)
{
    ODLinkSpecData *somThis = ODLinkSpecGetData(somSelf);
    ODLinkSpecMethodDebug("ODLinkSpec","GetProcessLaunchDate");

        #ifdef _PLATFORM_OS2_
        _interrupt( 3 );
        #else
        ProcessInfoRec info;

        info.processAppSpec = NULL;
        info.processName = NULL;
        info.processInfoLength = sizeof(info);

        if ( (GetProcessInformation(&_fProcessID, &info) == noErr) &&
                        (info.processLaunchDate == _fProcessLaunchDate) )
        {
                *psn = _fProcessID;
        }
        else
        {
                psn->lowLongOfPSN = kNoProcess;
                psn->highLongOfPSN = 0;
                ODSetSOMException(ev, kODErrCannotGetExternalLink);
        }
        #endif
}