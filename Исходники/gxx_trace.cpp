void __gxx_log__::log_out( int iWay,const wchar_t* tcszOutFormat,... )
{
	EnterCriticalSection(&m_cs);
	LogCreate();
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		return;
	}
	wchar_t *tOut = NULL;
	switch(iWay)
	{
	case __GXX_HIT:
		{
			tOut = L"提示";
		}
		break;
	case __GXX_WARNING:
		{
			tOut = L"警告";
		}
		break;
	case __GXX_ERROR:
		{
			tOut = L"错误";
		}
		break;
	case __GXX_BAD:
		{
			tOut = L"严重";
		}
		break;
	default:
		LeaveCriticalSection(&m_cs);
		return;
	}
	int strLen = wcslen(tcszOutFormat) ;
	if( strLen <= 0 )
	{
		LeaveCriticalSection(&m_cs);
		return;
	}
	wchar_t _wBuf[512];
	va_list  args;
	va_start(args,tcszOutFormat);
	vswprintf(_wBuf,tcszOutFormat,args);
	va_end(args);


	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	wchar_t outbuf[1024];
	swprintf(outbuf,L"%s! [ %d-%d-%d %d:%02d:%02d  ]: %s\r\n",
		tOut,
		stTime.wYear,stTime.wMonth,stTime.wDay,
		stTime.wHour,stTime.wMinute,stTime.wSecond,
		_wBuf);
	//写入buf完毕
	LONG longH = 0;
	if( ::SetFilePointer(m_hFile,0,&longH,FILE_END)>=0)
	{
		char _buf[2048];
		::WideCharToMultiByte( _AtlGetConversionACP(), 0, outbuf, wcslen(outbuf)+1, _buf, 2048, NULL, NULL );
		// 2014-4-11 - qsc
		if(IsNeedEncrypt())
		{
			Encrypt((BYTE*)_buf,strlen(_buf));
		}
		DWORD written = 0;
		::WriteFile(m_hFile,_buf,strlen(_buf),&written,NULL);
	}
	FlushFileBuffers(m_hFile);
	LeaveCriticalSection(&m_cs);
}