char* ReadRemoteDescriptorName(HANDLE hProcess, LPCVOID lpImageBaseAddress, 
							   PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor)
{
	char* pBuffer = new char[BUFFER_SIZE];

	BOOL bSuccess = ReadProcessMemory
	(
		hProcess,
		(LPCVOID)((DWORD)lpImageBaseAddress + pImageImportDescriptor->Name),
		pBuffer,
		BUFFER_SIZE,		
		0
	);

	if (!bSuccess)
		return 0;

	return pBuffer;
}