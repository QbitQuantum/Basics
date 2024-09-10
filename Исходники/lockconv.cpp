void __cdecl main ( )
{
    DWORD dwId=0;
    HANDLE hThread[MAXIMUM_WAIT_OBJECTS];
    DWORD dwRet=0;
    g_refCount=0;

    if(!InitializeCriticalSectionAndSpinCount(&g_cs, 4000))
    {
        return;
    }

    for(int i=0; i<MAXIMUM_WAIT_OBJECTS; i++)
    {
        hThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, &dwId);
        if(!hThread[i])
        {
            for(int j=0;j<i;j++)
            {   
                CloseHandle(hThread[j]);
                hThread[j]=NULL;
            }
            return;
        }
    }

    WaitForMultipleObjects(MAXIMUM_WAIT_OBJECTS, hThread, TRUE, INFINITE);
    for(int i=0; i<MAXIMUM_WAIT_OBJECTS; i++)
    {
        CloseHandle(hThread[i]);
        hThread[i]=NULL;
    }
}