OSStatus GetApplicationDirectory(FSSpec *workingDirectory) {
        ProcessSerialNumber PSN;
        ProcessInfoRec pinfo;
        OSErr	err;
        
                  /* set up process serial number */
        PSN.highLongOfPSN = 0;
        PSN.lowLongOfPSN = kCurrentProcess;
            /* set up info block */
        pinfo.processInfoLength = sizeof(pinfo);
        pinfo.processName = 0;
        pinfo.processAppSpec = workingDirectory;
        err = GetProcessInformation(&PSN, &pinfo);
        if (err == noErr && isSystem9_0_or_better()) {
#if TARGET_API_MAC_CARBON && !defined(__MWERKS__)
			FSMakeFSSpecCompat(workingDirectory->vRefNum, workingDirectory->parID,"\p:::",workingDirectory);
#else
			FSSpec	checkDirectory;
            FSMakeFSSpecCompat(workingDirectory->vRefNum, workingDirectory->parID,"\p:",&checkDirectory);
            if (strncmp((const char *)checkDirectory.name,(const char *) "\pMacOSClassic",13) == 0)
				FSMakeFSSpecCompat(workingDirectory->vRefNum, workingDirectory->parID,"\p:::",workingDirectory);
#endif
        }