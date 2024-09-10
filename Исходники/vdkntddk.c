//
//	Opens an image file
//
VDKSTAT
VdkOpenFile(
	IN HANDLE	*FileHandle,
	IN PCHAR	FileName,
	IN ULONG	NameLen,
	IN ULONG	ReadOnly)
{
	CHAR				buf[MAXIMUM_FILENAME_LENGTH];
	ULONG 				prefix;
	ANSI_STRING			ansi_name;
	UNICODE_STRING		unicode_name;
	OBJECT_ATTRIBUTES	attributes;
	IO_STATUS_BLOCK		io_status;
	VDKSTAT				status = VDK_OK;

	//
	// append appropriate prefix
	//
	prefix = 0;

	if (RtlCompareMemory(FileName, "\\??\\", 4) != 4) {

		RtlCopyMemory(buf, "\\??\\", 4);
		prefix = 4;

		if ((*FileName == '\\' || *FileName == '/') &&
			(*(FileName + 1) == '\\' || *(FileName + 1) == '/')) {
			//
			//	UNC path
			//
			RtlCopyMemory(buf + prefix, "UNC", 3);
			FileName++;
			NameLen--;
			prefix += 3;
		}
	}

	RtlCopyMemory(buf + prefix, FileName, NameLen);
	buf[NameLen + prefix] = '\0';

	VDKTRACE(VDKOPEN | VDKINFO,
		("[VDK] Opening file %s for %s\n",
			buf, ReadOnly ? "read-only" : "read-write"));

	//
	// generate unicode filename
	//
	RtlInitAnsiString(&ansi_name, buf);

	status = RtlAnsiStringToUnicodeString(
		&unicode_name, 	&ansi_name, TRUE);

	if (!VDKSUCCESS(status)) {

		VDKTRACE(VDKOPEN,
			("[VDK] Failed to convert filename to UNICODE\n"));

		return status;
	}

	//
	// open the file
	//
	InitializeObjectAttributes(
		&attributes,
		&unicode_name,
		OBJ_CASE_INSENSITIVE,
		NULL,
		NULL);

	status = ZwCreateFile(
		FileHandle,
		ReadOnly ? GENERIC_READ : (GENERIC_READ | GENERIC_WRITE),
		&attributes,
		&io_status,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		ReadOnly ? FILE_SHARE_READ : 0,
		FILE_OPEN,
		FILE_NON_DIRECTORY_FILE |
		FILE_RANDOM_ACCESS |
		FILE_NO_INTERMEDIATE_BUFFERING |
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);

	RtlFreeUnicodeString(&unicode_name);

	if (!VDKSUCCESS(status)) {
		VDKTRACE(VDKOPEN,
			("[VDK] ZwCreateFile - %s\n",
			VdkStatusStr(status)));

		*FileHandle = NULL;
	}

	return status;
}