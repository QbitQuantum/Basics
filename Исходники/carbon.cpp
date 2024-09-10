internal void
CarbonApplicationLaunched(ProcessSerialNumber PSN)
{
    Str255 ProcessName = {};
    ProcessInfoRec ProcessInfo = {};
    ProcessInfo.processInfoLength = sizeof(ProcessInfoRec);
    ProcessInfo.processName = ProcessName;

    /* NOTE(koekeishiya): Deprecated, consider switching to
     * CFDictionaryRef ProcessInformationCopyDictionary(const ProcessSerialNumber *PSN, UInt32 infoToReturn) */
    GetProcessInformation(&PSN, &ProcessInfo);

    char ProcessNameCString[256] = {0};
    if(ProcessInfo.processName)
        CopyPascalStringToC(ProcessInfo.processName, ProcessNameCString);
    std::string Name = ProcessNameCString;

    /* NOTE(koekeishiya): Check if we should care about this process. */
    if((!IsProcessWhitelisted(Name)) &&
       ((ProcessInfo.processMode & modeOnlyBackground) != 0))
        return;

    pid_t PID = 0;
    GetProcessPID(&PSN, &PID);

    /*
    printf("Carbon: Application launched %s\n", Name.c_str());
    printf("%d: modeReserved\n", ProcessInfo.processMode & modeReserved);
    printf("%d: modeControlPanel\n", ProcessInfo.processMode & modeControlPanel);
    printf("%d: modeLaunchDontSwitch\n", ProcessInfo.processMode & modeLaunchDontSwitch);
    printf("%d: modeDeskAccessory\n", ProcessInfo.processMode & modeDeskAccessory);
    printf("%d: modeMultiLaunch\n", ProcessInfo.processMode & modeMultiLaunch);
    printf("%d: modeNeedSuspendResume\n", ProcessInfo.processMode & modeNeedSuspendResume);
    printf("%d: modeCanBackground\n", ProcessInfo.processMode & modeCanBackground);
    printf("%d: modeDoesActivateOnFGSwitch\n", ProcessInfo.processMode & modeDoesActivateOnFGSwitch);
    printf("%d: modeOnlyBackground\n", ProcessInfo.processMode & modeOnlyBackground);
    printf("%d: modeGetFrontClicks\n", ProcessInfo.processMode & modeGetFrontClicks);
    printf("%d: modeGetAppDiedMsg\n", ProcessInfo.processMode & modeGetAppDiedMsg);
    printf("%d: mode32BitCompatible\n", ProcessInfo.processMode & mode32BitCompatible);
    printf("%d: modeHighLevelEventAware\n", ProcessInfo.processMode & modeHighLevelEventAware);
    printf("%d: modeLocalAndRemoteHLEvents\n", ProcessInfo.processMode & modeLocalAndRemoteHLEvents);
    printf("%d: modeStationeryAware\n", ProcessInfo.processMode & modeStationeryAware);
    printf("%d: modeUseTextEditServices\n", ProcessInfo.processMode & modeUseTextEditServices);
    printf("%d: modeDisplayManagerAware\n", ProcessInfo.processMode & modeDisplayManagerAware);
    */

    (*Applications)[PID] = AXLibConstructApplication(PID, Name);
    ax_application *Application = &(*Applications)[PID];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.5 * NSEC_PER_SEC), dispatch_get_main_queue(),
    ^{
        if(AXLibInitializeApplication(Application->PID))
            AXLibInitializedApplication(Application);
    });