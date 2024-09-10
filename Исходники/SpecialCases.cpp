DWORD SpecialCases::Sp_WriteFileEx()
	{
	BOOL returnVal_Real = 0;
	BOOL returnVal_Intercepted = 0;
	
    HANDLE h = "";

	DWORD error = 0;
	DWORD dwBuffer = 0;
	
	LPOVERLAPPED lpo = new OVERLAPPED;
	lpo->hEvent = 0;
	lpo->Internal = 0;
	lpo->InternalHigh = 0;
	lpo->Offset = 0;
	lpo->OffsetHigh = 0;
	return(WriteFileEx(h, &dwBuffer, 0, lpo, NULL));
	}