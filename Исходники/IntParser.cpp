BOOL ProcessApiMon::INTViewer(IntVisitor& Visitor)
{
	IMAGE_DOS_HEADER* pDos;
	IMAGE_NT_HEADERS* pNt;
	IMAGE_DATA_DIRECTORY* pDataDir;
	IMAGE_IMPORT_DESCRIPTOR* piid;

	HANDLE hProcess = NULL;
	LPVOID pBuf = NULL;
	BOOL ret = FALSE;
	DWORD nBytes;


	if (!(hProcess = OpenProcess(PROCESS_VM_READ, NULL, m_dwPid)))
	{
		printf("OpenProcess failed[%d]\n", GetLastError());
		return FALSE;
	}

	pBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_ModuleBaseSize);
	if (!pBuf)
	{
		printf("HeapAlloc failed[%d]\n", GetLastError());
		goto $Cleanup;
	}

	if (!ReadProcessMemory(hProcess, m_ModulepBaseMem, pBuf, m_ModuleBaseSize, &nBytes))
	{
		printf("ReadProcessMemory failed[%d]\n", GetLastError());
		goto $Cleanup;
	}

	pDos = (IMAGE_DOS_HEADER*)pBuf;
	if (pDos->e_magic != IMAGE_DOS_SIGNATURE)
		goto $Cleanup;

	pNt = (IMAGE_NT_HEADERS*)XGetPtr(pBuf, (DWORD_PTR)pDos->e_lfanew);

	if (pNt->Signature != IMAGE_NT_SIGNATURE)
		goto $Cleanup;

	pDataDir = &pNt->OptionalHeader.DataDirectory[1];
	piid = (IMAGE_IMPORT_DESCRIPTOR*)XGetPtr(pBuf, (DWORD_PTR)pDataDir->VirtualAddress);

	for (DWORD i = 0; piid[i].Name; i++)
	{
		try
		{
			if (!Visitor.visit(piid[i], pBuf))
				break;
		}
		catch (...)
		{
			goto $Cleanup;
		}
	}
	ret = TRUE;

$Cleanup:
	if (hProcess)
		CloseHandle(hProcess);

	if (pBuf)
		HeapFree(GetProcessHeap(), 0, pBuf);

	return ret;
}