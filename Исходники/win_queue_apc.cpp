EXPORT_SYM
VOID CALLBACK My_APCProc(ULONG_PTR dwParam)
{
    beenHere++;
    if(dwParam == 1)
    {
        return;
    }
    QueueUserAPC(My_APCProc, GetCurrentThread() , dwParam - 1);
    DWORD status = SleepEx(INFINITE , true);
    printf("SleepEx status = 0x%x \n" ,status);
}