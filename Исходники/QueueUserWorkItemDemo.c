int _tmain(int argc, _TCHAR *argv[])
{
    int i;

    for (i = 0; i < 10; ++i)
    {
        if (!QueueUserWorkItem(ThreadProc, (LPVOID)i, WT_EXECUTEDEFAULT))
            _ftprintf(stderr, _T("Failed to queue user worker item %d.\n"), i);
    }

    _putts(_T("Done!"));

    Sleep(1000);

    _putts(_T("-------------------------------------------------------------------------------"));

    for (i = 10; i < 20; ++i)
    {
        if (!QueueUserWorkItem(ThreadProc, (LPVOID)i, WT_EXECUTEDEFAULT))
            _ftprintf(stderr, _T("Failed to queue user worker item %d.\n"), i);
    }
    
    _tsystem(_T("pause"));

    return 0;
}