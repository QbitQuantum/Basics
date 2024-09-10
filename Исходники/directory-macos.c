 OSStatus GetApplicationDirectory(short *vRefNum, long *dirID) {
     ProcessSerialNumber PSN;
     ProcessInfoRec pinfo;
     FSSpec pspec;
     OSStatus err;
         /* valid parameters */
     if (vRefNum == NULL || dirID == NULL) return paramErr;
         /* set up process serial number */
     PSN.highLongOfPSN = 0;
     PSN.lowLongOfPSN = kCurrentProcess;
         /* set up info block */
     pinfo.processInfoLength = sizeof(pinfo);
     pinfo.processName = NULL;
     pinfo.processAppSpec = &pspec;
         /* grab the vrefnum and directory */
     err = GetProcessInformation(&PSN, &pinfo);
     if (err == noErr) {
         *vRefNum = pspec.vRefNum;
         *dirID = pspec.parID;
     }
     return err;
 }