//获取视频第5秒的截图
bool CCommonInterface::GetVideoPic(std::wstring lsVideoPath, std::wstring &lsPicPath, int iTimes, std::wstring strCachePath)
{
	//ffmpeg -ss 5 -i test.mp4 -f image2 -y  -s 350x240 test1.jpg
	//如果没有指定本地路径，先要获取一个临时路径用于存储生成的图片
	if (lsPicPath.length() <= 0)
	{
		wstring strFilePath = strCachePath;
		strFilePath += _T("\\TempPic\\");
		if (!PathFileExists(strFilePath.c_str()))
		{
			CCommonInterface comter;
			comter.CreateDir(strFilePath);
		}
		SYSTEMTIME stime = { 0 };
		GetLocalTime(&stime);
		TCHAR szCurrentTime[MAX_PATH] = { 0 };
		_stprintf(szCurrentTime, _T("%s%02d%02d%02d%02d%02d%04d.jpg"),
			_T("Pic"), stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);
		strFilePath += szCurrentTime;
		lsPicPath = strFilePath;
	}
	CCommonInterface ComInterface;
	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = _T("open");
	sei.nShow = SW_NORMAL;
	TCHAR szCacheUpdateTempPath[MAX_PATH] = { 0 };
	wstring strFfmpegPath = strCachePath;
	strFfmpegPath += _T("\\Ffmpeg\\ffmpeg.exe");
	TCHAR szParames[MAX_PATH * 2] = { 0 };
	StringCchPrintf(szParames, MAX_PATH * 2, _T("-ss %d -i \"%s\" -f image2 -y -s 854x480 \"%s\""),
		iTimes,
		lsVideoPath.c_str(),
		lsPicPath.c_str());
	sei.lpFile = strFfmpegPath.c_str();
	sei.lpParameters = szParames;
	sei.nShow = SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//GetLogFun(Info)(_T("....ffmpeg的参数%s"), sei.lpParameters);
	if (ShellExecuteEx(&sei))
	{
		//等待进程结束
		WaitForSingleObject(sei.hProcess, INFINITE);
		return true;
	}
	return false;
}