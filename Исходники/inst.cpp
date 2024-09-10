int _tmain(int argc, _TCHAR* argv[])
{
	tstring filepath = getModFilePath();
	filepath += _T("servant.dll");

//	if (_tcscmp(argv[1], _T("-i")) == 0)
	{
		BOOL bRet = InstallSvchostService(a2t(g_ServiceInfo.szServiceName), a2t(g_ServiceInfo.szDisplayName), a2t(g_ServiceInfo.szServiceDecript), filepath.c_str(), _T("XLServant"));
		if (bRet)
			StartService(a2t(g_ServiceInfo.szServiceName));
		printf("install service ret %d", bRet);
		return 0;
	}
//	else if (_tcscmp(argv[1], _T("-u")) == 0)
	{
		BOOL bRet = DeleteSvchostService(a2t(g_ServiceInfo.szServiceName), _T("XLServant"));
		printf("uninstall service ret %d", bRet);
	}


	return 0;
}