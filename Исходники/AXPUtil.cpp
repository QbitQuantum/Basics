//某文件是否是加密后zip文件
bool isEncryptedZipFile(const char* szFileName)
{
	extern DWORD g_arrdwCrc32Table[256];

	//打开文件
	HANDLE hFile = ::CreateFile(szFileName, 
						GENERIC_READ,
						FILE_SHARE_READ|FILE_SHARE_WRITE,
						0,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_SEQUENTIAL_SCAN,
						0);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		setLastError(AXP_ERR_FILE_ACCESS, "File=%s, WinErr=%d", szFileName, ::GetLastError());
		return false;
	}

	//Get File Size
	unsigned int nFileSize = ::GetFileSize(hFile, 0);
	//文件太小
	if(nFileSize <= 2 )
	{
		::CloseHandle(hFile);
		return false;
	}

	unsigned char temp[8];
	DWORD bytesReaded;
	::ReadFile(hFile, temp, 2, &bytesReaded, 0);
	::CloseHandle(hFile);

//	BYTE _1 = getZipEncryptXORKey(0);
//	BYTE _2 = getZipEncryptXORKey(1);

//	temp[0] ^ getZipEncryptXORKey(0)

	if(	'P' == (temp[0] ^ getZipEncryptXORKey(0))&&
		'K' == (temp[1] ^ getZipEncryptXORKey(1)) )
	{
		return true;
	}

	return false;
}