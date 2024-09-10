BOOL My_RegSetValueA()
{
	HKEY hKey=NULL;
	LPCSTR lpSubKey=NULL;
	DWORD dwType=NULL;
	LPCSTR lpData=NULL;
	DWORD cbData=NULL;
	LONG returnVal_Real = NULL;
	LONG returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = RegSetValueA (hKey,lpSubKey,dwType,lpData,cbData);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = RegSetValueA (hKey,lpSubKey,dwType,lpData,cbData);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}