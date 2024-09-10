// Given a PID attempt to find or create a DbgTransportSession instance to manage a connection to a runtime in
// that process. Returns E_UNEXPECTED if the process can't be found. Also returns a handle that can be waited
// on for process termination.
HRESULT DbgTransportTarget::GetTransportForProcess(DWORD                   dwPID,
                                                   DbgTransportSession   **ppTransport,
                                                   HANDLE                 *phProcessHandle)
{
    RSLockHolder lock(&m_sLock);
    HRESULT hr = S_OK;

    ProcessEntry *entry = LocateProcessByPID(dwPID);

    if (entry == NULL)
    {

       NewHolder<ProcessEntry> newEntry = new(nothrow) ProcessEntry();
       if (newEntry == NULL)
           return E_OUTOFMEMORY;

       NewHolder<DbgTransportSession> transport = new(nothrow) DbgTransportSession();
       if (transport == NULL)
       {
           return E_OUTOFMEMORY;
       }


       HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
       if (hProcess == NULL)
       {
           transport->Shutdown();
           return HRESULT_FROM_GetLastError();
       }

       // Initialize it (this immediately starts the remote connection process).
       hr = transport->Init(dwPID, hProcess);
       if (FAILED(hr))
       {
           transport->Shutdown();
           CloseHandle(hProcess);
           return hr;
       }

       entry = newEntry;
       newEntry.SuppressRelease();   
       entry->m_dwPID = dwPID;
       entry->m_hProcess = hProcess;
       entry->m_transport = transport;
       transport.SuppressRelease();
       entry->m_cProcessRef = 0;

       // Adding new entry to the list.
       entry->m_pNext = m_pProcessList;
       m_pProcessList = entry;
    }

    entry->m_cProcessRef++;
    _ASSERTE(entry->m_cProcessRef > 0);
    _ASSERTE(entry->m_transport != NULL);
    _ASSERTE(entry->m_hProcess > 0);
    
    *ppTransport = entry->m_transport;
    if (!DuplicateHandle(GetCurrentProcess(), 
                         entry->m_hProcess,
                         GetCurrentProcess(), 
                         phProcessHandle,
                         0,      // ignored since we are going to pass DUPLICATE_SAME_ACCESS
                         FALSE, 
                         DUPLICATE_SAME_ACCESS))
    {
        return HRESULT_FROM_GetLastError();
    }

    return hr;
}