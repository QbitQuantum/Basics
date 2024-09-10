void SetUpQD(void)
{
    ProcessSerialNumber PSN;
    FSSpec              myFSSpec;
    Str63               name;
    ProcessInfoRec      infoRec;
    OSErr               result = noErr;
    CFragConnectionID   connID;
    Str255              errName;

    // Memorize the plugin¹s resource file refnum for later use.
    gResFile = CurResFile();

#if !TARGET_API_MAC_CARBON
    // Ask the system if CFM is available.
    long response;
    OSErr err = Gestalt(gestaltCFMAttr, &response);
    Boolean hasCFM = BitTst(&response, 31-gestaltCFMPresent);

    if (hasCFM) {
        // GetProcessInformation takes a process serial number and
        // will give us back the name and FSSpec of the application.
        // See the Process Manager in IM.
        infoRec.processInfoLength = sizeof(ProcessInfoRec);
        infoRec.processName = name;
        infoRec.processAppSpec = &myFSSpec;

        PSN.highLongOfPSN = 0;
        PSN.lowLongOfPSN = kCurrentProcess;

        result = GetProcessInformation(&PSN, &infoRec);
    } else {
        // If no CFM installed, assume it must be a 68K app.
        result = -1;
    }

    if (result == noErr) {
        // Now that we know the app name and FSSpec, we can call
        // GetDiskFragmentto get a connID to use in a subsequent call
        // to FindSymbol (it will also return the address of ³main² in
        // app, which we ignore). If GetDiskFragment returns an
        // error, we assume the app must be 68K.
        Ptr mainAddr;
        result =  GetDiskFragment(infoRec.processAppSpec, 0L, 0L,
                                  infoRec.processName, kReferenceCFrag,
                                  &connID, (Ptr*)&mainAddr, errName);
    }

    if (result == noErr) {
        // The app is a PPC code fragment, so call FindSymbol
        // to get the exported ³qd² symbol so we can access its
        // QuickDraw globals.
        CFragSymbolClass symClass;
        result = FindSymbol(connID, "\pqd", (Ptr*)&gQDPtr, &symClass);
    } else {