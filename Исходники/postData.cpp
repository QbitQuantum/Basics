BOOL CPostData::UseHttpSendReqEx( std::string& lpost)
{
	long lgg;
	lgg = lpost.size();

	USES_CONVERSION;
	INTERNET_BUFFERS BufferIn;
	DWORD dwBytesWritten;

	BOOL bRet;

	TCHAR head[1024];        
	std::wstring strt = MS_CONTENTTYPE;
	std::wstring strt1 = CA2W(CSNManager::GetInstance()->GetSN().c_str());
	_stprintf_s(head, _countof(head), _T("%s\r\nSN: %s;\r\nMoneyhubUID: %s;\r\n"), strt.c_str() ,strt1.c_str() ,m_strHWID.c_str());
	//TCHAR head[]= strt.c_str(); 

	BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS ); // Must be set or error will occur
    BufferIn.Next = NULL; 
    BufferIn.lpcszHeader = head;
    BufferIn.dwHeadersLength = 0;
    BufferIn.dwHeadersTotal = sizeof(head);
    BufferIn.lpvBuffer = (LPSTR)lpost.c_str();                
    BufferIn.dwBufferLength = 0;
    BufferIn.dwBufferTotal = lgg; // This is the only member used other than dwStructSize
    BufferIn.dwOffsetLow = 0;
    BufferIn.dwOffsetHigh = 0;

    if(!HttpSendRequestEx( m_hInetFile, &BufferIn, NULL, 0, 2))
    {
		CloseHandles();
        printf( "Error on HttpSendRequestEx %d\n",GetLastError() );
        return FALSE;
    }

	bRet=TRUE;
	bRet = InternetWriteFile( m_hInetFile, (LPSTR)lpost.c_str(), lgg, &dwBytesWritten);

	if(!bRet)
	{
     	CloseHandles();
        printf( "\nError on InternetWriteFile %lu\n",GetLastError() );
        return FALSE;
    }

	bRet = HttpEndRequest(m_hInetFile, NULL, 0, 0);
    if(!bRet)
    {
    	CloseHandles();
        printf( "Error on HttpEndRequest %lu \n", GetLastError());
        return FALSE;
    }

		char pcBuffer[BUFFSIZE];
		DWORD dwBytesRead;
	    LPSTR	lpszData1;
		lpszData1 = new char[1024*1024];
		lpszData1[0]='\0';

		//printf("\nThe following was returned by the server:\n");
		do
		{	dwBytesRead=0;
			if(InternetReadFile(m_hInetFile, pcBuffer, BUFFSIZE-1, &dwBytesRead))
			{
				pcBuffer[dwBytesRead]=0x00; // Null-terminate buffer
        		strcat(lpszData1,pcBuffer);
				//printf("%s", pcBuffer);
			}
			else
                return FALSE;
				//lpszData1 ="";
				//printf("\nInternetReadFile failed");
		}while(dwBytesRead>0);
		//printf("\n");
		lpost = "";
		lpost = CW2A(UTF8ToUnicode(lpszData1).c_str());
	    delete []lpszData1;

	CloseHandles();
	//return  ERR_SUCCESS;
	return TRUE;
}