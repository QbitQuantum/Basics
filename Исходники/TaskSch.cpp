void Jobadd() {
	DWORD JobId, ret;
	AT_INFO ai;
	TCHAR *filepath;
	TCHAR RootPath[MAX_PATH];
	GetSystemDirectory(RootPath, MAX_PATH);
	filepath = new TCHAR[wcslen(RootPath) + MAX_PATH];
	wcscpy_s(filepath, wcslen(RootPath)+10 , RootPath);
	TCHAR *strPadPath = _T("\\notepad.exe");
	int len = wcslen(strPadPath);
	wcscat_s(filepath, wcslen(RootPath) + MAX_PATH-2, strPadPath); //完整路径
	memset(&ai, 0, sizeof(ai));
	ai.Command = filepath;
	ai.DaysOfMonth = 0;
	ai.DaysOfWeek = 0x7F; //7F等于二进制的7个1，就是每周的7天全部运行
	ai.Flags = JOB_RUN_PERIODICALLY;
	ai.JobTime = 22 * 60 * 60 * 1000 + 21 * 60 * 1000; //22点21分，这里是以毫秒为单位的，所以需要乘这些值
	ret = NetScheduleJobAdd(NULL, LPBYTE(&ai), &JobId);
	if (ret == ERROR_SUCCESS)
		std::cout << " SUCCESS!!"<< "job time is : "<< ai.JobTime/60/1000/60<<":"<<ai.JobTime/60/1000%60 << std::endl;
	else
		std::cout << "Error" << std::endl;
}