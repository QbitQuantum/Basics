/*---------------------------------------------------------------------------*\
| UNLOCK WINDOW INFO
|   This routine unlocks the memory the caller has previously locked.
\*---------------------------------------------------------------------------*/
BOOL FAR UnlockWindowInfo(HWND hWnd)
{
    HANDLE hMem;


    if(hMem = (HANDLE)GetWindowLongPtr(hWnd,0))
        if(!LocalUnlock(hMem))
            return(TRUE);

    return(FALSE);
}