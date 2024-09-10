void CSimpleLog::Add(const char* fmt, ...)
{



	if(!m_fp)
	{

		// 设置当前目录为流媒体主程序目录
		std::string app_path = GetAppPath();

		app_path = app_path + m_logdir;

		_mkdir(app_path.c_str());


		struct tm *now;
		time_t ltime;

		time(&ltime);
		now = localtime(&ltime);

		char chFile[512] = {0};
	
		

		sprintf_s(chFile, "%s\\Log_%d_%d_%d %02d_%02d_%02d.log", app_path.c_str()
			, now->tm_year+1900, now->tm_mon+1, now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);


		m_fp = fopen(chFile, "w+"); //以添加的方式输出到文件
		if (!m_fp)
			return;

	}



	/*-----------------------进入临界区(写文件)------------------------------*/	
	::EnterCriticalSection(&m_crit);   
	try      
	{
		va_list argptr;          //分析字符串的格式
		va_start(argptr, fmt);
		_vsnprintf(m_tBuf, BUFSIZE, fmt, argptr);
		va_end(argptr);
	}
	catch (...)
	{
		m_tBuf[0] = 0;
	}


	char szDate[64] = {0};
	char szTime[64] = {0};
	_strdate_s(szDate);
	_strtime_s(szTime);

	fprintf(m_fp,"%s %s\t", szDate, szTime);
	fprintf(m_fp, "%s\n", m_tBuf);	
	fflush(m_fp);

	::LeaveCriticalSection(&m_crit);  
	/*----------------------------退出临界区---------------------------------*/	

}