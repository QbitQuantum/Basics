// TODO: implement this using real CoreFoundation API instead of Carbon API
wxString wxStandardPathsCF::GetExecutablePath() const
{
#ifdef __WXMAC__
    ProcessInfoRec processinfo;
    ProcessSerialNumber procno ;
    FSSpec fsSpec;

    procno.highLongOfPSN = 0 ;
    procno.lowLongOfPSN = kCurrentProcess ;
    processinfo.processInfoLength = sizeof(ProcessInfoRec);
    processinfo.processName = NULL;
    processinfo.processAppSpec = &fsSpec;

    GetProcessInformation( &procno , &processinfo ) ;
    return wxMacFSSpec2MacFilename(&fsSpec);
#else
    return wxStandardPathsBase::GetExecutablePath();
#endif
}