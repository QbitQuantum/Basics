DWORD WINAPI StarServerShutdownProc(LPVOID link)
{
    StarServer* stars = (StarServer*) link;

    Sleep(3000);

    if (stars) {
        stars->Exit();
        return 0;
    }

    return (DWORD) E_POINTER;
}