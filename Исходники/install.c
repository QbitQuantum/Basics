///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Reads or writes specified number of sectors from/to specified buffer.
//
static	BOOL	DirectIo(
			   PWCHAR	Drive,			// drive name to read/write sectors from/to
			   PCHAR	Buffer,			// bufer to store the data
			   ULONG	Length,			// size of the buffer
			   ULONG	LBASector,		// starting LBA sector
			   ULONG	Count,			// number of sectors to read/write
			   ULONG	Flags			// variouse operation flags
			   )
{
	BOOL		Ret = FALSE;
	HANDLE		hDrive;
	NTSTATUS	ntStatus;
	OBJECT_ATTRIBUTES	oa = {0};
	UNICODE_STRING		us;
	IO_STATUS_BLOCK		IoStatus = {0};
	LARGE_INTEGER		FilePos = {0};
	HANDLE				hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	RtlInitUnicodeString(&us, Drive);
	InitializeObjectAttributes(&oa, &us, OBJ_CASE_INSENSITIVE, NULL, NULL);

	if ((Count * BIOS_DEFAULT_SECTOR_SIZE) <= Length)
	{
		ntStatus = NtCreateFile(&hDrive, GENERIC_WRITE | GENERIC_READ, &oa, &IoStatus, NULL, FILE_ATTRIBUTE_NORMAL,
								FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, 0, NULL, 0);
	
		if (NT_SUCCESS(ntStatus))
		{
			FilePos.QuadPart = ((ULONGLONG)LBASector * BIOS_DEFAULT_SECTOR_SIZE);

			if (Flags & SCSI_IO_WRITE_SECTOR)
				ntStatus = NtWriteFile(hDrive, hEvent, NULL, NULL, &IoStatus, Buffer, (Count*BIOS_DEFAULT_SECTOR_SIZE), &FilePos, NULL);
			else
				ntStatus = NtReadFile(hDrive, hEvent, NULL, NULL, &IoStatus, Buffer, (Count*BIOS_DEFAULT_SECTOR_SIZE), &FilePos, NULL);

			if (ntStatus == STATUS_PENDING)
				WaitForSingleObject(hEvent, INFINITE);

			NtClose(hDrive);

			if (NT_SUCCESS(IoStatus.Status))
				Ret = TRUE;
		}	// if (hDrive != INVALID_HANDLE_VALUE)
	}	// 	if ((Count * BIOS_DEFAULT_SECTOR_SIZE) <= Length)
 
   return(Ret);
}