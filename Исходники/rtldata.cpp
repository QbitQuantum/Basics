void _RTLDataClass::operator delete(void *ptr)
{
    HANDLE hMem = LOWORD(GlobalHandle(FP_SEG(ptr)));
    if (hMem)
        if (GlobalUnlock(hMem))
            GlobalFree(hMem);
}