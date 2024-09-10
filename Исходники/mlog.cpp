/**
 *	writeLog	-		写日志文件
 *
 *	@log_type	[in]	写日志的等级(信息/警告/出错)
 *	@fmt		[in]	需要写的日志信息
 *
 *	return
 *		无
 */
void MWriteLog::writeLog(unsigned char log_type, const char *fmt, ...)
{
#define		MAX_LOG_LEN			10240
#define		LOG_LINE			"\n"

	char					buffer[MAX_LOG_LEN] = {0};
	va_list					ap;
	int						rc;
	int						err;
	SYSTEMTIME				sys;
	MLocalSection			locSec;
	
	locSec.Attch(&m_Lock);
	if(!m_bNeedWriteDisk)
		return;

	GetLocalTime(&sys);

	if(detectLogFile(sys) != 0)
		return;

	switch (log_type)
	{
	case LOG_TYPE_INFO:
		rc = _snprintf(buffer, sizeof(buffer), 
			"[信息] (%04d-%02d-%02d %02d:%02d:%02d-%03d)<%s>\t\t", 
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,
			sys.wMinute,sys.wSecond,sys.wMilliseconds,
			m_cLogPreName);
		break;
	case LOG_TYPE_WARN:
		rc = _snprintf(buffer, sizeof(buffer), 
			"[警告] (%04d-%02d-%02d %02d:%02d:%02d-%03d)<%s>\t\t", 
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,
			sys.wMinute,sys.wSecond,sys.wMilliseconds,
			m_cLogPreName);
		break;
	case LOG_TYPE_ERROR:
		rc = _snprintf(buffer, sizeof(buffer), 
			"[错误] (%04d-%02d-%02d %02d:%02d:%02d-%03d)<%s>\t\t", 
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,
			sys.wMinute,sys.wSecond,sys.wMilliseconds,
			m_cLogPreName);
		break;
	default:
		rc = -1;
		break;
	}
	if(rc < 0)
		return;

	va_start(ap, fmt);
	err = _vsnprintf(buffer+rc, MAX_LOG_LEN-rc-2, fmt, ap);
	if(err < 0)
		rc += _snprintf(buffer+rc, MAX_LOG_LEN-rc-2, 
		"写日志文件时传入的长度过大，写日志缓冲区不够");
	else
		rc += err;

	rc += _snprintf(buffer+rc, sizeof(LOG_LINE), LOG_LINE);
	va_end(ap);

	
	if(m_pFile != NULL && rc < MAX_LOG_LEN)
	{
		fwrite(buffer, sizeof(char), rc, m_pFile);
		fflush(m_pFile);
	}
#ifdef _DEBUG
	printf("%s\n", buffer);
#endif

#undef MAX_LOG_LEN
#undef LOG_LINE
}