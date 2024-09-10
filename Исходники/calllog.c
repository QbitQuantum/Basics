/*
 * fileMessage()
 *
 * This function handles the upload/download file log.
 */
void fileMessage(char mode, char *fn, char IsDL, int protocol, long size)
{
    long	  hours, mins;
    static label  LastActive = "";
    char	  logfn[100];
    /* int	 	  yr, dy, hr, mn; */
    char	  *mon, *pr, buf[100];
    static struct timeData gData, fData, xData;
    struct timeData *pData;
    static long xwork;
    static char fin_done;

    if (protocol == ASCII || cfg.Audit == 0)
	return;

    makeAuditName(logfn, "filelog.sys");
/*  getCdate(&yr, &mon, &dy, &hr, &mn); */
    getCdate(&gData.year, &mon, &gData.day, &gData.hour, &gData.minute);
    strcpy(gData.month, mon);

    switch (mode) {
    case FL_START:
	startTimer(USER_TIMER);
	fin_done = FALSE;
	fData = gData;
	break;
    case FL_FIN:
	fin_done = TRUE;
	xData = gData;
	xwork = chkTimeSince(USER_TIMER);
	break;
    case FL_SUCCESS:
    case FL_FAIL:
    case FL_EX_END:
	if (strCmpU(LastActive, logBuf.lbname) != SAMESTRING) {
	    sprintf(buf, "\n%s on %d%s%02d @ ", logBuf.lbname, gData.year, mon,
								gData.day);
	    if (BaudRate > 0l) 
		sprintf(lbyte(buf), "%ld", BaudRate);
	    else
		strcat(buf, "Unknown");

	    strcat(buf, ":");

	    CallMsg(logfn, buf);
	    strCpy(LastActive, logBuf.lbname);
	}
	if (!fin_done) {
	    xwork = chkTimeSince(USER_TIMER);
	    pData = &gData;
	}
	else
	    pData = &xData;
	hours = xwork / 3600;
	xwork -= (hours * 3600);
	mins  = xwork / 60;
	xwork -= (mins * 60);
	if (protocol > TOP_PROTOCOL)
	    pr = FindProtoName(protocol);
	else
	    pr = Table[protocol].GenericName;
	if (mode == FL_EX_END) {
	    sprintf(buf,
    "%2cFollowing files %c %s via %s %d:%02d - %d:%02d (%ld:%02ld:%02ld):",
		' ', (IsDL) ? 'D' : 'U', roomBuf.rbname, 
		pr,
		fData.hour, fData.minute, pData->hour, pData->minute,
		hours, mins, xwork);
	    CallMsg(logfn, buf);
	    CallMsg(logfn, msgBuf.mbtext);
	}
	else {
	    if (!IsDL && mode == FL_FAIL)
		sprintf(buf, "%2c%s (FAILED) %c %s: %d:%02d - %d:%02d (%ld:%02ld:%02ld) %s.",
		' ', fn, (IsDL) ? 'D' : 'U', roomBuf.rbname,
		fData.hour, fData.minute, pData->hour, pData->minute,
		hours, mins, xwork, pr);
	    else
		sprintf(buf,
    		"%2c%s (%ld) %c %s: %d:%02d - %d:%02d (%ld:%02ld:%02ld) %s. %s",
		' ', fn, size, (IsDL) ? 'D' : 'U', roomBuf.rbname,
		fData.hour, fData.minute, pData->hour, pData->minute,
		hours, mins, xwork, pr,
		(mode == FL_FAIL) ? "(FAILED)" : "");
	    CallMsg(logfn, buf);
	}
	break;
    }
}