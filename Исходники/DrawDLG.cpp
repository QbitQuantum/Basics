BOOL LocateQueue(CString m_strLabel, WCHAR *wcsFormatName, DWORD dwNumChars)
{
	//
	// Set restrictions to locate the drawing queue with the label specified.
	//
	DWORD cProps = 0;
	MQPROPERTYRESTRICTION aPropRestriction[2];
	MQRESTRICTION Restriction;

	aPropRestriction[cProps].rel           = PREQ;
	aPropRestriction[cProps].prop          = PROPID_Q_TYPE;
	aPropRestriction[cProps].prval.vt      = VT_CLSID;
	aPropRestriction[cProps].prval.puuid   = &guidDrawType;
	cProps++;

	WCHAR wcsLabel[MQ_MAX_Q_LABEL_LEN+1];
        size_t nResultedStringLength=0;
	mbstowcs_s(
            &nResultedStringLength,
            wcsLabel, 
            sizeof(wcsLabel)/sizeof(wcsLabel[0]),
            m_strLabel, 
            sizeof(wcsLabel)/sizeof(wcsLabel[0])-1
            );
	aPropRestriction[cProps].rel           = PREQ;
	aPropRestriction[cProps].prop          = PROPID_Q_LABEL;
	aPropRestriction[cProps].prval.vt      = VT_LPWSTR;
	aPropRestriction[cProps].prval.pwszVal = wcsLabel;
	cProps++;

	Restriction.cRes = cProps;
	Restriction.paPropRes = aPropRestriction;


	//
	// Request the queue instance for the queue specified.
	//
	cProps = 0;
	QUEUEPROPID aPropId[1];
	MQCOLUMNSET Column;
	
	aPropId[cProps] = PROPID_Q_INSTANCE;
	cProps++;

	Column.cCol = cProps;
	Column.aCol = aPropId;


	//
	// Locate the queue specified.
	//
	HANDLE hEnum;
	BOOL fFound = FALSE;
	HRESULT hr = MQLocateBegin(NULL, &Restriction, &Column, NULL, &hEnum);
	if (!FAILED(hr))
	{
	    MQPROPVARIANT aPropVar[1];
		DWORD cQueue = 1;
		hr = MQLocateNext(hEnum, &cQueue, aPropVar);
		if (!FAILED(hr) && cQueue > 0)
		{
			//
			// Obtain the format name for the queue located.
			//
			hr = MQInstanceToFormatName(aPropVar[0].puuid, wcsFormatName, &dwNumChars);
            MQFreeMemory(aPropVar[0].puuid);
			if (!FAILED(hr))
				fFound = TRUE;
		}

		MQLocateEnd(hEnum);
	}


    return fFound;
}