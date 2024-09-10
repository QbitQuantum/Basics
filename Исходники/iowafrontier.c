static void getappspec (FSSpec *fs) {
	
	ProcessSerialNumber psn;
	ProcessInfoRec info;
	Str255 s;
	
	GetCurrentProcess (&psn);
	
	info.processInfoLength = (long) sizeof (info);
	
	info.processName = s; /*place to store process name*/
	
	info.processAppSpec = fs; /*place to store process filespec*/
	
	GetProcessInformation (&psn, &info);
	} /*getappspec*/