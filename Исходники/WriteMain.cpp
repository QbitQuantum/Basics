BOOL CWriteMain::Start(
	LPCWSTR fileName,
	BOOL overWriteFlag,
	ULONGLONG createSize
	)
{
	Stop();

	this->savePath = fileName;
	_OutputDebugString(L"★CWriteMain::Start CreateFile:%s\r\n", this->savePath.c_str());
	this->file = _CreateDirectoryAndFile(this->savePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, overWriteFlag ? CREATE_ALWAYS : CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if( this->file == INVALID_HANDLE_VALUE ){
		_OutputDebugString(L"★CWriteMain::Start Err:0x%08X\r\n", GetLastError());
		WCHAR szPath[_MAX_PATH];
		WCHAR szDrive[_MAX_DRIVE];
		WCHAR szDir[_MAX_DIR];
		WCHAR szFname[_MAX_FNAME];
		WCHAR szExt[_MAX_EXT];
		_wsplitpath_s(fileName, szDrive, szDir, szFname, szExt);
		_wmakepath_s(szPath, szDrive, szDir, szFname, NULL);
		for( int i = 1; ; i++ ){
			Format(this->savePath, L"%s-(%d)%s", szPath, i, szExt);
			this->file = CreateFile(this->savePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, overWriteFlag ? CREATE_ALWAYS : CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			if( this->file != INVALID_HANDLE_VALUE || i >= 999 ){
				DWORD err = GetLastError();
				_OutputDebugString(L"★CWriteMain::Start CreateFile:%s\r\n", this->savePath.c_str());
				if( this->file != INVALID_HANDLE_VALUE ){
					break;
				}
				_OutputDebugString(L"★CWriteMain::Start Err:0x%08X\r\n", err);
				this->savePath = L"";
				return FALSE;
			}
		}
	}

	//ディスクに容量を確保
	if( createSize > 0 ){
		LARGE_INTEGER stPos;
		stPos.QuadPart = createSize;
		SetFilePointerEx( this->file, stPos, NULL, FILE_BEGIN );
		SetEndOfFile( this->file );
		SetFilePointer( this->file, 0, NULL, FILE_BEGIN );
	}
	this->wrotePos = 0;

	//コマンドに分岐出力
	if( this->teeCmd.empty() == false ){
		this->teeFile = CreateFile(this->savePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if( this->teeFile != INVALID_HANDLE_VALUE ){
			this->teeThreadStopFlag = FALSE;
			this->teeThread = (HANDLE)_beginthreadex(NULL, 0, TeeThread, this, 0, NULL);
		}
	}

	return TRUE;
}