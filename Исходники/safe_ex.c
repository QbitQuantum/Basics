BOOL WINAPI in_whitelist(LPCWSTR lpfile)
{
	WCHAR *moz_processes[] = {L"", L"plugin-container.exe", L"plugin-hang-ui.exe", L"webapprt-stub.exe",
							  L"webapp-uninstaller.exe",L"WSEnable.exe",L"uninstall\\helper.exe",
							  L"crashreporter.exe",L"CommandExecuteHandler.exe",L"maintenanceservice.exe",
							  L"maintenanceservice_installer.exe",L"updater.exe"
							 };
	static  WCHAR white_list[EXCLUDE_NUM][VALUE_LEN+1];
	int		i = sizeof(moz_processes)/sizeof(moz_processes[0]);
	LPCWSTR pname = lpfile;
	BOOL    ret = FALSE;
	if (lpfile[0] == L'"')
	{
		pname = &lpfile[1];
	}
	/* 遍历白名单一次,只需遍历一次 */
	ret = stristrW(white_list[1],L"plugin-container.exe") != NULL;
	if ( !ret )
	{
		/* firefox目录下进程的路径 */
		int num;
		WCHAR temp[VALUE_LEN+1];
		GetModuleFileNameW(NULL,temp,VALUE_LEN);
		wcsncpy(white_list[0],(LPCWSTR)temp,VALUE_LEN);
		PathRemoveFileSpecW(temp);
		for(num=1; num<i; ++num)
		{
			_snwprintf(white_list[num],VALUE_LEN,L"%ls\\%ls", temp, moz_processes[num]);
		}
		ret = foreach_section(L"whitelist", &white_list[num], EXCLUDE_NUM-num);
	}
	if ( (ret = !ret) == FALSE )
	{
		/* 核对白名单 */
		for ( i=0; i<EXCLUDE_NUM ; i++ )
		{
			if (wcslen(white_list[i]) == 0)
			{
				continue;
			}
			if ( StrChrW(white_list[i],L'*') || StrChrW(white_list[i],L'?') )
			{
				if ( PathMatchSpecW(pname,white_list[i]) )
				{
					ret = TRUE;
					break;
				}
			}
			else if (white_list[i][1] != L':')
			{
				PathToCombineW(white_list[i],VALUE_LEN);
			}
			if (_wcsnicmp(white_list[i],pname,wcslen(white_list[i]))==0)
			{
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}