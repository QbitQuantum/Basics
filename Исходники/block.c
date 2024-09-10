NTSTATUS co_os_open_file(char *pathname, PHANDLE FileHandle)
{    
	NTSTATUS status;
	OBJECT_ATTRIBUTES ObjectAttributes;
	IO_STATUS_BLOCK IoStatusBlock;
	UNICODE_STRING unipath;
	ANSI_STRING ansi;
    
	ansi.Buffer = pathname;
	ansi.Length = strlen(pathname);
	ansi.MaximumLength = ansi.Length + 1;

	RtlAnsiStringToUnicodeString(&unipath, &ansi, TRUE);

	InitializeObjectAttributes(&ObjectAttributes, 
				   &unipath,
				   OBJ_CASE_INSENSITIVE,
				   NULL,
				   NULL);

	status = ZwCreateFile(FileHandle, 
			      FILE_READ_DATA | FILE_WRITE_DATA | SYNCHRONIZE,
			      &ObjectAttributes,
			      &IoStatusBlock,
			      NULL,
			      0,
			      0,
			      FILE_OPEN,
			      FILE_SYNCHRONOUS_IO_NONALERT,
			      NULL,
			      0);

	if (status != STATUS_SUCCESS)
		co_debug("ZwOpenFile() returned error: %x\n", status);

	RtlFreeUnicodeString(&unipath);

	return status;
}