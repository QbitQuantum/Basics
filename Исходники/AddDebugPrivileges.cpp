void AddDebugPrivileges()
{
HANDLE hToken;
TOKEN_PRIVILEGES tP;
if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken)) return;
if(!LookupPrivilegeValueA(NULL,"SeDebugPrivilege",&tP.Privileges[0].Luid))
	{
	CloseHandle(hToken);
	return;
	}
tP.PrivilegeCount=1;
tP.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
AdjustTokenPrivileges(hToken,FALSE,&tP,0,NULL,0);
CloseHandle(hToken);
}