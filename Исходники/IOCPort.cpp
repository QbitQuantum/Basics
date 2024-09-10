void CIOCPort::CreateClientWorkerThread()
{
    HANDLE			hWorkerThread[MAX_USER];
    DWORD			WorkerId[MAX_USER];

    m_hClientIOCPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 10 );

    for(int i=0; i<(int)m_dwConcurrency; i++) {
        hWorkerThread[i] = ::CreateThread(
                               NULL,
                               0,
                               ClientWorkerThread,
                               (LPVOID)this,
                               0,
                               &WorkerId[i]
                           );
    }
}