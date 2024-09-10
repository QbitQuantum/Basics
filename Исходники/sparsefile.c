/*
 * print_file_size -- prints file size and its size on disk
 */
static void
print_file_size(const char *filename)
{
	LARGE_INTEGER filesize;
	FILE_COMPRESSION_INFO fci;

	HANDLE fh = CreateFileA(filename, GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fh == INVALID_HANDLE_VALUE) {
		out_err("CreateFile");
		return;
	}

	BOOL ret = GetFileSizeEx(fh, &filesize);
	if (ret == FALSE) {
		out_err("GetFileSizeEx");
		goto err;
	}

	ret = GetFileInformationByHandleEx(fh, FileCompressionInfo,
			&fci, sizeof(fci));
	if (ret == FALSE) {
		out_err("GetFileInformationByHandleEx");
		goto err;
	}

	if (filesize.QuadPart < 65536)
		fprintf(stderr, "\ntotal size: %lluB",
				filesize.QuadPart);
	else
		fprintf(stderr, "\ntotal size: %lluKB",
				filesize.QuadPart / 1024);

	if (fci.CompressedFileSize.QuadPart < 65536)
		fprintf(stderr, ", actual size on disk: %lluKB\n",
				fci.CompressedFileSize.QuadPart);
	else
		fprintf(stderr, ", actual size on disk: %lluKB\n",
				fci.CompressedFileSize.QuadPart / 1024);

err:
	CloseHandle(fh);
}