bool CWfpNET::Time_get(void) // Obtain Date and Time
{
	LPTIME_OF_DAY_INFO pTOD = NULL;
	NET_API_STATUS nStatus = NULL;
	DWORD mindiff = 0, hourdiff = 0;
	CString tmp;
	
	// The NetRemoteTOD function returns the time of day information from
	// a specified server.
	// No special group membership is required to successfully execute the
	// NetRemoteTOD function.

	nStatus = NetRemoteTOD(node.szComputerW, (LPBYTE *)&pTOD);
	
	if(nStatus == NERR_Success)
	{
		if(pTOD != NULL)
		{
			tmp.Format(_T("Date and Time:\n\t[%d/%d/%d] "),pTOD->tod_month, pTOD->tod_day, pTOD->tod_year);
			Time.Add(tmp);
			tmp.Format(_T(" -- %02lu:%02lu:%02lu.%02lu\n"), pTOD->tod_hours - (pTOD->tod_timezone / 60), pTOD->tod_mins, pTOD->tod_secs, pTOD->tod_hunds); 
			Time.Add(tmp);		
		}
	}
	else
	{
		ErrorHandler("NetRemoteTOD", nStatus);
	    return false;
	}
	if(pTOD != NULL)
      NetApiBufferFree(pTOD);

	return true;
}