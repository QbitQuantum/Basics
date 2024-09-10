CToshHandler::CToshHandler(TToshParams& aParams)
{
	iParams = aParams;

	memset(&iDevInfo,0,sizeof(iDevInfo));

	memset(&iPrevDevInfoList,0,sizeof(iPrevDevInfoList));
	

	iOpenedObexApi = false;
	iCID = 0;
	iSDPSSRESULT = NULL;

	iRFCOMMCID = 0;
//	iHFile = 0;


		GetModuleFileName(AfxGetInstanceHandle(), iTmpObexFilePath, MAX_PATH);
	
	 /* Search backward. */
	CHAR ch('\\');
	CHAR* pdest = strrchr( iTmpObexFilePath, ch );

	if( pdest != NULL )
	{
		if( MAX_PATH > pdest - iTmpObexFilePath)
			*(pdest+1) = NULL;
	}	
	
	
	StringCbCatA(iTmpObexFilePath,MAX_PATH,KWmxpJarPathRelativeToReleaseExe);

	//////////prepare tosh bt sdp struct iWmxpToshSDPPattern in ram
	iWmxpToshSDPPattern = NULL;
	iWmxpToshSDPPatternSize = 0;

	BTUUIDINFO aBTUUIDINFO;
	aBTUUIDINFO.wUUIDType = 128;
	
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[0] = 0x2b;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[1] = 0xc2;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[2] = 0xb9;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[3] = 0x2e;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[4] = 0x39;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[5] = 0x92;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[6] = 0x11;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[7] = 0xdc;

	((unsigned char*)&(aBTUUIDINFO.BtUUID))[8] = 0x83;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[9] = 0x14;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[10] = 0x08;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[11] = 0x00;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[12] = 0x20;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[13] = 0x0c;
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[14] = 0x9a;			
	((unsigned char*)&(aBTUUIDINFO.BtUUID))[15] = 0x66;	

	

	
	
	//BTUUIDLIST aBTUUIDLIST; cannot static because the declaration was BTUUIDINFO BtUUIDInfo[]; so we need to alloc for the first one too
	BTUUIDLIST* aPBTUUIDLIST = (PBTUUIDLIST) malloc(sizeof(BTUUIDLIST) + sizeof(BTUUIDINFO));
	aPBTUUIDLIST->dwUUIDInfoNum=1;
	memcpy(&(aPBTUUIDLIST->BtUUIDInfo[0]) ,&aBTUUIDINFO, sizeof(BTUUIDINFO));

	iWmxpToshSDPPattern = NULL;
	iWmxpToshAttrIdList = NULL;
	iMemSDP_SSA_Result = NULL;
	
	long status;
	if(BtMakeServiceSearchPattern2(aPBTUUIDLIST, &iWmxpToshSDPPatternSize, &iWmxpToshSDPPattern, &status))
	{
		;//ok 	

		//ShowHex(iWmxpToshSDPPattern,iWmxpToshSDPPatternSize);
			
		
		BTUNIVATTRIBUTE mask = 0;
		mask |= TOSBTAPI_ATR_PROTOCOLDESCRIPTORLIST;
		mask |= TOSBTAPI_ATR_SERVICERECORDHANDLE;
		if(BtMakeAttributeIDList2(mask, &iWmxpToshAttrIdListSize, &iWmxpToshAttrIdList, &iStatus))
			mydebug::log("th164");
		else
		{
			AfxMessageBox("BtMakeAttributeIDList2 failed");
			delete iWmxpToshAttrIdList;
			iWmxpToshAttrIdList = NULL;		
		}
			
	}
	else
	{
		AfxMessageBox("BtMakeServiceSearchPattern2 failed");
		delete iWmxpToshSDPPattern;
		iWmxpToshSDPPattern = NULL;
	}

	if(iWmxpToshSDPPattern ==NULL || aPBTUUIDLIST==NULL)
		AfxMessageBox("SearchPattern or UUID list generation failed");

	mydebug::log("th165");

	free(aPBTUUIDLIST);

	mydebug::log("th166");
	////////////////////////////

	
}