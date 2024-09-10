int		SSQ_Init(SS_QUEUE_OBJ_T *pObj, unsigned int sharememory, unsigned int channelid, wchar_t *sharename, unsigned int bufsize, unsigned int prerecordsecs, unsigned int createsharememory)
{
	wchar_t wszHeaderName[36] = {0,};
	wchar_t wszFramelistName[36] = {0,};
	wchar_t wszDataName[36] = {0,};
	if (NULL==pObj)											return -1;
	if (createsharememory==0x01 && bufsize<1)				return -1;
	if ( (sharememory==0x01) && (NULL==sharename || (0==wcscmp(sharename, TEXT("\0")))) )	return -1;

	memset(pObj, 0x00, sizeof(SS_QUEUE_OBJ_T));
	pObj->channelid = channelid;
	pObj->shareinfo.id = channelid;
	wcscpy(pObj->shareinfo.name, sharename);

	wchar_t wszMutexName[36] = {0,};
	wsprintf(wszMutexName, TEXT("%s%d_mutex"), sharename, channelid);
	pObj->hMutex = OpenMutex(NULL, FALSE, wszMutexName);
	if (NULL == pObj->hMutex)
	{
		pObj->hMutex = CreateMutex(NULL, FALSE, wszMutexName);
		if (NULL == pObj->hMutex)							return -1;
	}

	//Create Header map
	
	
#ifdef _WIN32
	if (sharememory == 0x01)
	{
		wsprintf(wszHeaderName, TEXT("%s%d_h"), sharename, channelid);
		pObj->hSSHeader = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wszHeaderName);
		if (NULL==pObj->hSSHeader && createsharememory==0x01)
		{
			pObj->hSSHeader = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE|SEC_COMMIT, 0, sizeof(SS_HEADER_T), wszHeaderName);
			if (NULL==pObj->hSSHeader || pObj->hSSHeader==INVALID_HANDLE_VALUE)
			{
				return -1;
			}
		}
		pObj->pQueHeader = (SS_HEADER_T*)MapViewOfFile(pObj->hSSHeader, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, 0);
		if (createsharememory==0x01)
		{
			if (pObj->pQueHeader->bufsize < 1)
			{
				memset(pObj->pQueHeader, 0x00, sizeof(SS_HEADER_T));
				pObj->pQueHeader->bufsize = bufsize;
			}
		}
		else if (NULL==pObj->pQueHeader)
		{
			return -1;
		}
		else
		{
			bufsize = pObj->pQueHeader->bufsize;
 		}
	}
	else
	{
		pObj->pQueHeader = new SS_HEADER_T;
		memset(pObj->pQueHeader, 0x00, sizeof(SS_HEADER_T));
	}

	//==========================================
	//Create frame list map
	if (prerecordsecs > 0)
	{
		wsprintf(wszFramelistName, TEXT("%s%d_f"), sharename, channelid);
		unsigned int nFramelistNum = prerecordsecs * 30;	//每秒30帧
		unsigned int nFrameQueSize = nFramelistNum*sizeof(FRAMEINFO_LIST_T);

		if (sharememory == 0x01)
		{
			pObj->hSSFrameList = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wszFramelistName);
			if (NULL==pObj->hSSFrameList && createsharememory==0x01)
			{
				pObj->hSSFrameList = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE|SEC_COMMIT, 0, nFrameQueSize, wszFramelistName);
				if (NULL==pObj->hSSFrameList || pObj->hSSFrameList==INVALID_HANDLE_VALUE)
				{
					return -1;
				}
			}
			pObj->pFrameinfoList = (FRAMEINFO_LIST_T*)MapViewOfFile(pObj->hSSFrameList, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, 0);
			if (createsharememory==0x01)
			{
				memset(pObj->pFrameinfoList, 0x00, nFrameQueSize);
				pObj->pQueHeader->framelistNum = nFramelistNum;
			}
			else if (NULL==pObj->hSSFrameList)
			{
				return -1;
			}
		}
		else
		{
			pObj->pFrameinfoList = new FRAMEINFO_LIST_T[nFramelistNum];
			memset(&pObj->pFrameinfoList[0], 0x00, sizeof(FRAMEINFO_LIST_T)*nFramelistNum);
			pObj->pQueHeader->framelistNum = nFramelistNum;
		}
	}

	//Create data map
	
	if (sharememory == 0x01)
	{
		wsprintf(wszDataName, TEXT("%s%d_b"), sharename, channelid);
		pObj->hSSData	= OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, wszDataName);
		if (NULL==pObj->hSSData && createsharememory==0x01)
		{
			pObj->hSSData = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE|SEC_COMMIT, 0, bufsize, wszDataName);
		}
		if (NULL == pObj->hSSData || pObj->hSSData==INVALID_HANDLE_VALUE)
		{
			return -1;
		}
		pObj->pQueData = (char*)MapViewOfFile(pObj->hSSData, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, 0);
	}
	else
	{
		pObj->pQueData = new char [bufsize];
		pObj->pQueHeader->bufsize = bufsize;
	}
	if (createsharememory==0x01)
	{
		//memset(pQueHeader, 0x00, sizeof(SS_HEADER_T));
		memset(pObj->pQueData, 0x00, bufsize);
	}
#else
	int ret = shm_create((SYNC_VID_SHM_KEY<<8)|channelid, &pObj->shmHdrid, sizeof(SS_HEADER_T), (char**)&pObj->pQueHeader);
	if (ret < 0)
	{
		return -1;
	}
	SSQ_TRACE("[%d]pQueHeader: %d\n", (SYNC_VID_SHM_KEY<<8)|channelid, pObj->shmHdrid);
	ret = shm_create((SYNC_VID_SHM_KEY<<16)|channelid, &pObj->shmDatid, bufsize, (char**)&pObj->pQueData);
	if (ret < 0)
	{
		shm_delete(&pObj->shmHdrid, (char*)pObj->pQueHeader);
		return -1;
	}
	pObj->pQueHeader->bufsize = bufsize;
	SSQ_TRACE("[%d]pQueData: %d\n", (SYNC_VID_SHM_KEY<<16)|channelid, pObj->shmDatid);
#endif

	return 0;
}