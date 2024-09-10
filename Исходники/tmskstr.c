DWORD
WaitCommThread(
    LPVOID Trash
    )
{

    DWORD ReasonSatisfied;
    DWORD Trash2;
    OVERLAPPED Ol;
    UNREFERENCED_PARAMETER(Trash);

    Ol.hEvent = WaitEvent;
    do {

        if (!WaitCommEvent(
                 hFile,
                 &ReasonSatisfied,
                 &Ol
                 )) {

            DWORD LastError = GetLastError();

            if (LastError == ERROR_IO_PENDING) {

                if (!GetOverlappedResult(
                         hFile,
                         &Ol,
                         &Trash2,
                         TRUE
                         )) {

                    WaitForSingleObject(IoSemaphore,-1);
                    printf("Could not do the getoverlapped on the wait: %d\n",GetLastError());
                    ReleaseSemaphore(IoSemaphore,1,NULL);

                }

            } else {

                WaitForSingleObject(IoSemaphore,-1);
                printf("Could not start the wait: %d\n",LastError);
                ReleaseSemaphore(IoSemaphore,1,NULL);

            }

        }

    } while (TRUE);

    return 1;

}