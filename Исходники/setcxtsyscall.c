static DWORD WINAPI
ThreadProc1(LPVOID parm)
{
    LARGE_INTEGER waittime;
    NTSTATUS res;
    HANDLE e;
    GET_NTDLL(NtWaitForSingleObject,
              (IN HANDLE ObjectHandle, IN BOOLEAN Alertable, IN PLARGE_INTEGER TimeOut));
    print("starting thread...\n");

    e = CreateEvent(NULL, FALSE, FALSE, "foo");
    waittime.QuadPart = -((int)500 * TIMER_UNITS_PER_MILLISECOND);
    control = 1;
    do {
        res = NtWaitForSingleObject(e, false /* not alertable */, &waittime);
    } while (control);
    __asm {
        mov   reg_eax, eax
        mov   reg_ebx, ebx
        mov   reg_ecx, ecx
        mov   reg_edx, edx
        mov   reg_edi, edi
        mov   reg_esi, esi
        mov   reg_esp, esp
        mov   reg_ebp, ebp
    }
    print("res is " PFMT " but shouldn't get here!!!\n", res);
#if VERBOSE
    print("registers: " PFMT " " PFMT " " PFMT " " PFMT " " PFMT " " PFMT " " PFMT
          " " PFMT "\n",
          reg_eax, reg_ebx, reg_ecx, reg_edx, reg_edi, reg_esi, reg_esp, reg_ebp);
#endif
    CloseHandle(e);

    print("exiting thread\n");
    return -1;
}