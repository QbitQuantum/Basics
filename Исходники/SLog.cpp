	/// <summary>
	/// <para name='Name'>SLog::getDateTimeString</para>
	/// <para name='Purpose'>Return a formatted date time string</para>
	/// </summary>
	/// <param name='logFormat'>indicate whether to return the date time string in log format or decoration format</param>
	/// <returns>a formatted date/time string</returns>
	/// <remarks>
	/// <para name='Notes'></para>
	/// <para name='Author'>Kenn Guilstorf</para>
	/// <para name='LastModified'>2015-10-26</para>
	/// </remarks>
	TSTRING SLog::getDateTimeString(bool logFormat)
	{
		TSTRING retValue;
		TSTRING strFormat;
		TCHAR* chBuffer = new TCHAR[50];
		SYSTEMTIME st;

		if (logFormat)
		{
			strFormat = TSTRING(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d | "));
		}
		else
		{
			strFormat = TSTRING(_T(".%04d%02d%02d.%02d%02d%02d%03d"));
		}

		GetLocalTime(&st);

		SPRINTF(chBuffer,
			50,
			strFormat.c_str(),
			(int)st.wYear, 
			(int)st.wMonth, 
			(int)st.wDay, 
			(int)st.wHour, 
			(int)st.wMinute, 
			(int)st.wSecond, 
			(int)st.wMilliseconds);
		
		retValue = TSTRING(chBuffer);

		return retValue;
	}