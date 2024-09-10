//enum processes
void CDlgProcList::EnumProc2List()
{
	if(ZwQuerySystemInformation!=NULL)
    {
		HANDLE hHeap = GetProcessHeap();

		NTSTATUS Status;
		ULONG cbBuffer = 0x8000;
		PVOID pBuffer = NULL;

		do
		{
			pBuffer = HeapAlloc(hHeap, 0, cbBuffer);
			if (pBuffer == NULL)
				return;

			Status = ZwQuerySystemInformation(
				SystemProcessesAndThreadsInformation,
				pBuffer, cbBuffer, NULL);

			if (Status == STATUS_INFO_LENGTH_MISMATCH)
			{
				HeapFree(hHeap, 0, pBuffer);
				cbBuffer *= 2;
			}
			else if (!NT_SUCCESS(Status))
			{
				HeapFree(hHeap, 0, pBuffer);
				return;
			}
		}
		while (Status == STATUS_INFO_LENGTH_MISMATCH);

		PSYSTEM_PROCESS_INFORMATION pProcesses = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

		for (;;)
		{
			PCWSTR pszProcessName = pProcesses->ProcessName.Buffer;
			
			
			if (pszProcessName == NULL)
				pszProcessName = L"Idle";

			USES_CONVERSION;
			std::string strProcessName=W2A(pszProcessName);
			/*m_processlists.insert(std::make_pair(strProcessName,pProcesses->ProcessId));*/
			FillRecord2List(strProcessName.c_str(),pProcesses->ProcessId);
			if (pProcesses->NextEntryDelta == 0)
				break;

			// find the address of the next process structure
			pProcesses = (PSYSTEM_PROCESS_INFORMATION)(((LPBYTE)pProcesses)
				+ pProcesses->NextEntryDelta);
		}

		HeapFree(hHeap, 0, pBuffer);
	}


	if(m_processlists.size()!=0)
    {
		std::map<std::string,DWORD>::iterator iter;
		for(iter=m_processlists.begin();iter!=m_processlists.end();iter++)
        {
			FillRecord2List(iter->first.c_str(),iter->second);
		}
	}
}