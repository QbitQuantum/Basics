int main()
{
	_THANDLE tindex;

	Buffer buf(0, 500);
#ifdef linux
	int ret = createthread(tindex, WorkThread, &buf);
	if (ret != 0)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "createthread error(%d).", errno);
		return 0;
	}
#else	// _WIN32
	createthread(tindex, WorkThread, &buf);
	if (tindex == NULL)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "createthread error(%d).", GetLastError());
		return 0;
	}
#endif // linux

	FILE* fWrite = fopen(WRITE_FILE_PATH, "wb");
	if (fWrite == NULL)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "fopen WRITE_FILE_PATH error %d.", errno);
		assert(false);
	}

	unsigned int nLen = 0;
	char readbuf[101];
	while (1)
	{
		nLen = buf.GetCanReadSize();
		if (nLen > 0)
		{
			memset(readbuf, 0, 101);
			nLen = buf.ReadData(readbuf, 100);
			fwrite(readbuf, 1, nLen, fWrite);
			fflush(fWrite);
			//WriteLog(FC_GREEN, STDOUT_FILE_HANDLE, readbuf);
		}
		csf_sleep(1000);
	}

	return 0;
}