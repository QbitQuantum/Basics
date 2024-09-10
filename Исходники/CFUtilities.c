static unsigned __stdcall __CFWinThreadFunc(void *arg) {
    struct _args *args = (struct _args*)arg; 
    ((void (*)(void *))args->func)(args->arg);
    CloseHandle(args->handle);
    CFAllocatorDeallocate(kCFAllocatorSystemDefault, arg);
    _endthreadex(0);
    return 0; 
}