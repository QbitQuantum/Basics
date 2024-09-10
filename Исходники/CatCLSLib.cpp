STDAPI DllRegisterPerUser()
{
	return DllInstall(TRUE, _T("user"));
}