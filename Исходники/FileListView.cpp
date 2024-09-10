const char* CFileListView::ConvertTime( const time_t* pFileTime )
{
	static char szBuffer[1024];
	tm localTime;

	assert(pFileTime != NULL);

	localtime_s(&localTime, pFileTime);

	sprintf_s(szBuffer, 1024, "%d/%d/%d %.2d:%.2d",
		localTime.tm_year + 1900,
		localTime.tm_mon + 1,
		localTime.tm_mday,
		localTime.tm_hour,
		localTime.tm_min);

	return szBuffer;
}