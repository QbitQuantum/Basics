void DtaTimeLogDate(FILE * fdlog, const char * string)
{
	wchar_t lpDateStr[20];
	wchar_t lpTimeStr[10];
	char DateStr[20];
	char TimeStr[10];
	SYSTEMTIME wSystemTime;

   GetSystemTime(&wSystemTime);

   // Get Date
   GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &wSystemTime, L"ddd','MMM dd yyyy", 
	   lpDateStr, 20);
   WideCharToMultiByte(CP_ACP, 0, lpDateStr,  -1, DateStr, 20, 0, 0);

   // Get Time
   GetTimeFormatW(LOCALE_SYSTEM_DEFAULT, 0, &wSystemTime, L"HH':'mm':'ss", 
	   lpTimeStr, 10);
   WideCharToMultiByte(CP_ACP, 0, lpTimeStr,  -1, TimeStr, 10, 0, 0);
   fprintf(fdlog, "%s %s %s\n", string, DateStr, TimeStr);
   fflush(fdlog);
}