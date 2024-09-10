//----------------------------------------------------------------------------
void CLogSupport::WriteLog(AnsiString content){
	DWORD dwFileLenHigh;
	DWORD dwFileLen = GetFileSize(handleFile , &dwFileLenHigh);
	if (dwFileLen > (DWORD)logSize * 1024){    //文件过大 清空文件
		SetFilePointer(handleFile , 0 , NULL , FILE_BEGIN);    //移动文件指针
		SetEndOfFile(handleFile);//清空文件
	}
	AnsiString strContent =content +"\r\n";
	::EnterCriticalSection(&m_cs);
	SetFilePointer(handleFile , 0 , NULL , FILE_END);    //移动到文件末尾
	DWORD dwWriteLen;
	WriteFile(handleFile, strContent.c_str(), (DWORD)strContent.Length(), &dwWriteLen, NULL);
	::LeaveCriticalSection(&m_cs);	//释放临界区
}