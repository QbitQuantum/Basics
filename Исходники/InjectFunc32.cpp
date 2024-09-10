BOOL __stdcall HsIs32BitFile(const WCHAR * pwszFullPath)
{
	FILE * peFile = NULL;
	_wfopen_s(&peFile, pwszFullPath, L"rb");
	if (peFile == NULL)
	{
		fclose(peFile);
		return -1;
	}

	IMAGE_DOS_HEADER imageDosHeader;
	fread(&imageDosHeader, sizeof(IMAGE_DOS_HEADER), 1, peFile);
	if (imageDosHeader.e_magic != IMAGE_DOS_SIGNATURE)
	{
		fclose(peFile);
		return FALSE;
	}

	IMAGE_NT_HEADERS imageNtHeaders;
	fseek(peFile, imageDosHeader.e_lfanew, SEEK_SET);
	fread(&imageNtHeaders, sizeof(IMAGE_NT_HEADERS), 1, peFile);
	fclose(peFile);
	if (imageNtHeaders.Signature != IMAGE_NT_SIGNATURE)
	{
		return FALSE;
	}

	if (imageNtHeaders.FileHeader.Machine == IMAGE_FILE_MACHINE_I386)
	{
		return TRUE;
	}
	// 	if (imageNtHeaders.FileHeader.Machine == IMAGE_FILE_MACHINE_IA64 ||
	// 		imageNtHeaders.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64)
	// 	{
	// 		return FALSE;	//64BIT
	// 	}

	return FALSE;
}