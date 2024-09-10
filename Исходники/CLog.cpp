bool cLog::Print(const char *szText, ...)
/////////////////////////////////////////////////////////////////////////////////////
{
	va_list l_va;
	__time64_t ltime;
	_time64( &ltime );

	char timedate [ 80 ];

	sprintf ( timedate, _ctime64 ( &ltime ));
	timedate[strlen(timedate) - 1] = 0;

	//Initialize variable argument list
	va_start(l_va, szText);

	//Open the log file for append
	if((m_file= fopen(LOG_FILENAME, "a+"))==NULL)
		return false;

	//Write the text and a newline
	fprintf (m_file, "%s : ", timedate);
	vfprintf(m_file, szText, l_va);
	putc('\n', m_file);

	//Close the file
	fclose(m_file);

	va_end(l_va);

	return true;
}