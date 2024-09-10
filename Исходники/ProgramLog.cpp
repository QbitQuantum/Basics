CProgramLog::~CProgramLog()
{
	DeleteCriticalSection(&m_kCritical);
	char buf[128];
	char tmpTime[32];
	char tmpDate[32];
	_strtime(tmpTime);
	_strdate(tmpDate);

	sprintf(buf, "EndTime: 【%s %s】\r\n", tmpDate, tmpTime);
	LogFileWrite(buf, strlen(buf));
}