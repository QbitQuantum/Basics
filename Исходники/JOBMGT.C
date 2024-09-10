DWORD FindProcessId (DWORD jobNumber)

/* Obtain the process ID of the specified job number. */
{
	HANDLE hJobData;
	JM_JOB jobRecord;
	DWORD nXfer, fileSizeLow;
	TCHAR jobMgtFileName[MAX_PATH+1];
	OVERLAPPED regionStart;
	LARGE_INTEGER fileSize;

	if ( !GetJobMgtFileName (jobMgtFileName) ) return 0;
	hJobData = CreateFile (jobMgtFileName, GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hJobData == INVALID_HANDLE_VALUE) return 0;
	/* Position to the correct record, but not past the end of file */
	/* As a variation, use GetFileSize to demonstrate its operation. */
	if (!GetFileSizeEx (hJobData, &fileSize) ||
		(fileSize.HighPart != 0 || SJM_JOB * (jobNumber - 1) > fileSize.LowPart 
		 || fileSize.LowPart > SJM_JOB * MAX_JOBS_ALLOWED))
			return 0;
	fileSizeLow = fileSize.LowPart;
	/* SetFilePoiner is more convenient here than SetFilePointerEx since the the file is known to be "short" ( < 4 GB). */
	SetFilePointer (hJobData, SJM_JOB * (jobNumber - 1), NULL, FILE_BEGIN);
	
	/* Get a shared lock on the record. */
	
	regionStart.Offset = SJM_JOB * (jobNumber - 1);
	regionStart.OffsetHigh = 0; /* Assume a "short" file. */
	regionStart.hEvent = (HANDLE)0;
	LockFileEx (hJobData, 0, 0, SJM_JOB, 0, &regionStart);
	
	if (!ReadFile (hJobData, &jobRecord, SJM_JOB, &nXfer, NULL))
		ReportError (_T ("JobData file error"), 0, TRUE);

	UnlockFileEx (hJobData, 0, SJM_JOB, 0, &regionStart);
	CloseHandle (hJobData);

	return jobRecord.ProcessId;
}