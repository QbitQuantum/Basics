BOOL DoMapShareChange(BOOL removeUnknown)
{
    DRIVEMAPLIST List;
    TCHAR szMachine[ MAX_PATH],szPath[MAX_PATH];
    DWORD rc=28;
    HANDLE hEnum;
    LPNETRESOURCE lpnrLocal,lpnr=NULL;
    DWORD res;
    DWORD cEntries=-1;
    DWORD cbBuffer=16384;

    memset(szMachine, '\0', sizeof(szMachine));
    GetClientNetbiosName(szMachine);

    // Initialize the data structure
    if (!IsServiceActive())
	return TRUE;
    memset (&List, 0x00, sizeof(DRIVEMAPLIST));
    for (size_t ii = 0; ii < 26; ++ii)
	List.aDriveMap[ii].chDrive = chDRIVE_A + ii;
    QueryDriveMapList_ReadSubmounts (&List);
    if ((res=WNetOpenEnum(RESOURCE_CONNECTED,RESOURCETYPE_DISK,RESOURCEUSAGE_CONNECTABLE,lpnr,&hEnum))!=NO_ERROR)
	return FALSE;
    lpnrLocal=(LPNETRESOURCE) GlobalAlloc(GPTR,cbBuffer);
    sprintf(szPath,"\\\\%s\\",szMachine);
    _strlwr(szPath);
    do {
        /* Reset lpnrLocal and cEntries before each call */
	memset(lpnrLocal,0,cbBuffer);
        cEntries = -1;

        if ((res = WNetEnumResource(hEnum,&cEntries,lpnrLocal,&cbBuffer))==NO_ERROR)
	{
	    for (DWORD i=0;i<cEntries;i++)
	    {
		if (strstr(_strlwr(lpnrLocal[i].lpRemoteName),szPath)==NULL)
		    continue;	//only look at real afs mappings
		CHAR * pSubmount=strrchr(lpnrLocal[i].lpRemoteName,'\\')+1;
		if (lstrcmpi(pSubmount,"all")==0)
		    continue;				// do not remove 'all'
		for (DWORD j=0;j<List.cSubmounts;j++)
		{
		    if ((List.aSubmounts[j].szSubmount[0]) &&
			 (lstrcmpi(List.aSubmounts[j].szSubmount,pSubmount)==0)
			 )
		    {
			List.aSubmounts[j].fInUse=TRUE;
			goto nextname;
		    }
		}
		// wasn't on list so lets remove
		DisMountDOSDrive(pSubmount);
	      nextname:;
	    }
	}
    } while (res == NO_ERROR);
    GlobalFree((HGLOBAL)lpnrLocal);
    WNetCloseEnum(hEnum);
    sprintf(szPath,"\\\\%s\\all",szMachine);

    // Lets connect all submounts that weren't connectd
    DWORD cbUser=MAXRANDOMNAMELEN-1;
    CHAR szUser[MAXRANDOMNAMELEN];
    CHAR * pUser = NULL;
    if (WNetGetUser(szPath,(LPSTR)szUser,&cbUser)==NO_ERROR) {
	if ((pUser=strchr(szUser,'\\'))!=NULL)
            pUser++;
    }

    for (DWORD j=0;j<List.cSubmounts;j++)
    {
	if (List.aSubmounts[j].fInUse)
	    continue;
	DWORD res=MountDOSDrive(0,List.aSubmounts[j].szSubmount,FALSE,pUser);
    }
    return TRUE;
}