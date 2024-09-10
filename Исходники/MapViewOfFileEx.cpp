BOOL My_MapViewOfFileEx()
{
	HANDLE hFileMappingObject=NULL;
	DWORD dwDesiredAccess=NULL;
	DWORD dwFileOffsetHigh=NULL;
	DWORD dwFileOffsetLow=NULL;
	SIZE_T dwNumberOfBytesToMap=NULL;
	LPVOID lpBaseAddress=NULL;
	LPVOID returnVal_Real = NULL;
	LPVOID returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = MapViewOfFileEx (hFileMappingObject,dwDesiredAccess,dwFileOffsetHigh,dwFileOffsetLow,dwNumberOfBytesToMap,lpBaseAddress);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = MapViewOfFileEx (hFileMappingObject,dwDesiredAccess,dwFileOffsetHigh,dwFileOffsetLow,dwNumberOfBytesToMap,lpBaseAddress);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}