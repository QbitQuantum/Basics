void SetTimeFromTP(ULONG ulTime)	// 根据时间协议返回的时间设置系统时间
{
	// Windows文件时间是一个64位的值，它是从1601年1月1日中午12:00到现在的时间间隔，
	// 单位是1/1000 0000秒，即1000万分之1秒（100-nanosecond ）
	FILETIME ft;
	SYSTEMTIME st;

	// 首先将基准时间（1900年1月1日0点0分0秒0毫秒）转化为Windows文件时间	
	st.wYear = 1900;
	st.wMonth = 1;
	st.wDay = 1;
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;
	SystemTimeToFileTime(&st, &ft);

	// 然后将Time Protocol使用的基准时间加上以及逝去的时间，即ulTime
	LONGLONG *pLLong = (LONGLONG *)&ft;
	// 注意，文件时间单位是1/1000 0000秒，即1000万分之1秒（100-nanosecond ）
	*pLLong += (LONGLONG)10000000 * ulTime; 

	// 再将时间转化回来，更新系统时间
	FileTimeToSystemTime(&ft, &st);	
	SetSystemTime(&st);
}