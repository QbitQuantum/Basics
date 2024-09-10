BOOL  PALAPI StartThreadTest()
{
    HMODULE hLib;
    HANDLE  hThread;  
    DWORD   dwThreadId;
    LPTHREAD_START_ROUTINE lpStartAddress =  &CreateTestThread;
    LPVOID lpParameter = lpStartAddress;
    DWORD rc = -1;
    /*Load library (DLL).*/
    hLib = LoadLibrary(LibraryName);
    if(hLib == NULL)
    {
        Trace("ERROR: Unable to load library %s\n", LibraryName);
        
        return (FALSE);
    }

    /*Start the test thread*/
    hThread = CreateThread(NULL, 
                            (DWORD)0,
                            lpParameter,
                            hLib,
                            (DWORD)NULL,
                            &dwThreadId);
    if(hThread == NULL)
    {
        Trace("ERROR:%u: Unable to create thread.\n",
                GetLastError());

        FreeLibrary(hLib);
        return (FALSE);
    }

    /*Wait on thread.*/
    rc = WaitForSingleObject(hThread, TIMEOUT);
    if( rc != WAIT_OBJECT_0 )
    {
        Trace("ERROR:%u: hThread=0x%4.4lx not exited by "
            "FreeLibraryAndExitThread, RC[%d]\n",
            GetLastError(),  
            hThread, rc);

// There is a possibility that the other thread might 
// still be using the library VSW:337893
//        FreeLibrary(hLib);
        CloseHandle(hThread);
        return (FALSE);
    }
            
    /*Test access to DLL.*/
    if(!TestDll(hLib, 0))
    {
        Trace("ERROR: TestDll function returned FALSE "
            "expected TRUE\n.");
        
        CloseHandle(hThread);
        return (FALSE);
    }

    FreeLibrary(hLib);
    /*Clean-up thread.*/
    CloseHandle(hThread);

    return (TRUE);
}