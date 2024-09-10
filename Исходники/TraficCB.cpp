void TrafficInformation::InitFile(__int64 sz,LPCSTR SrcName,LPCSTR DestName)
{
	if(FullFileSize != -1)
	{
		TotalComplete++;
		TotalFiles    = Max(TotalFiles, TotalSkipped+TotalComplete);
		TotalSize    += FullFileSize;
		TotalFullSize = Max(TotalSize, TotalFullSize);
	}

	if(sz == -1) sz = 0;

	FullFileSize       = sz;
	FileSize           = 0;
	LastSize           = 0;
	StartFileSize      = 0;
	Cps                = 0;
	FileStartTime      = time(NULL);
	FileWaitTime       = 0;
	AvCps[0] = 0; AvCps[1] = 0; AvCps[2] = 0;
	GET_TIME(LastTime);
	StrCpy(SrcFileName,  SrcName,  ARRAYSIZE(SrcFileName));
	StrCpy(DestFileName, DestName, ARRAYSIZE(DestFileName));
}