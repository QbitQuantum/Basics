int ADM_unlink(const char *filename)
{
#ifdef __WIN32
	int filenameLength = utf8StringToWideChar(filename, -1, NULL);
	wchar_t wcFilename[filenameLength];

	utf8StringToWideChar(filename, -1, wcFilename);

	return _wunlink(wcFilename);
#else
	return unlink(filename);
#endif
}