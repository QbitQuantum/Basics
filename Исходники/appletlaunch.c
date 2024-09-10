static Boolean appRunning (OSType appid) {
	
	/*
	return true if the server application is running. 
	*/
	
	ProcessInfoRec info;
	ProcessSerialNumber psn;
	Str255 bsname;
	FSSpec fss;
	
	info.processInfoLength = sizeof (info);
	
	info.processName = bsname; /*place to store process name*/
	
	info.processAppSpec = &fss; /*place to store process filespec*/
	
	psn.highLongOfPSN = kNoProcess;
	
	psn.lowLongOfPSN = kNoProcess;
	
	while (GetNextProcess (&psn) == noErr) {
		
	 	info.processInfoLength = sizeof (ProcessInfoRec);
	 	
		if (GetProcessInformation (&psn, &info) != noErr)
			continue; /*keep going -- ignore error*/
		
		if (info.processSignature == appid)
			return (true);
		} /*while*/
	
	return (false); /*loop completed, no server*/
	} /*appRunning*/