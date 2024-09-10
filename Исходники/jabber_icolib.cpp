static int LoadAdvancedIcons(int iID)
{
	int i;
	char * proto=TransportProtoTable[iID].proto;    
	char * defFile[MAX_PATH]={0};
	char * Group[255];
	char * Uname[255];
	int first=-1;
	HICON empty=LoadSmallIcon(NULL,MAKEINTRESOURCE(102));

	_snprintf((char *)Group, sizeof(Group),"%s/%s/%s %s",Translate("Status Icons"), jabberModuleName, proto, Translate("transport"));
	_snprintf((char *)defFile, sizeof(defFile),"proto_%s.dll",proto);
	if (!hAdvancedStatusIcon)
		hAdvancedStatusIcon=(HIMAGELIST)CallService(MS_CLIST_GETICONSIMAGELIST,0,0);
	
	EnterCriticalSection( &modeMsgMutex );
	for (i=0; i<ID_STATUS_ONTHEPHONE-ID_STATUS_OFFLINE; i++) {
		HICON hicon;        
		BOOL needFree;
		int n=skinStatusToJabberStatus[i];
		char * descr=(char*)CallService(MS_CLIST_GETSTATUSMODEDESCRIPTION,n+ID_STATUS_OFFLINE,0);
		_snprintf((char *)Uname, sizeof(Uname),"%s_Transport_%s_%d",jabberProtoName,proto,n);
		hicon=(HICON)LoadTransportIcon((char*)defFile,-skinIconStatusToResourceId[i],(char*)Uname,(char*)Group,(char*)descr,-(n+ID_STATUS_OFFLINE),&needFree);
		int index=(TransportProtoTable[iID].startIndex==-1)?-1:TransportProtoTable[iID].startIndex+n;
		int added=ImageList_ReplaceIcon(hAdvancedStatusIcon,index,hicon?hicon:empty);          
		if (first==-1) first=added;
		if (hicon && needFree) DestroyIcon(hicon);
	}

	if (TransportProtoTable[iID].startIndex == -1)
		TransportProtoTable[iID].startIndex = first;
	LeaveCriticalSection( &modeMsgMutex );
	return 0;
}