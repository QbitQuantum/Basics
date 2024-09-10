NTSTATUS NTAPI HookedNtContinue(PCONTEXT ThreadContext, BOOLEAN RaiseAlert) //restore DRx Registers
{
    DWORD_PTR retAddress = (DWORD_PTR)_ReturnAddress();
    if (!KiUserExceptionDispatcherAddress)
    {
        KiUserExceptionDispatcherAddress = (DWORD_PTR)GetProcAddress(DllExchange.hNtdll, "KiUserExceptionDispatcher");
    }

    if (ThreadContext)
    {
        //char text[100];
        //wsprintfA(text, "HookedNtContinue return %X", _ReturnAddress());
        //MessageBoxA(0, text, "debug", 0);

        if (retAddress >= KiUserExceptionDispatcherAddress && retAddress < (KiUserExceptionDispatcherAddress + 0x100))
        {
            int index = ThreadDebugContextFindExistingSlotIndex();
            if (index != -1)
            {
                ThreadContext->Dr0 = ArrayDebugRegister[index].Dr0;
                ThreadContext->Dr1 = ArrayDebugRegister[index].Dr1;
                ThreadContext->Dr2 = ArrayDebugRegister[index].Dr2;
                ThreadContext->Dr3 = ArrayDebugRegister[index].Dr3;
                ThreadContext->Dr6 = ArrayDebugRegister[index].Dr6;
                ThreadContext->Dr7 = ArrayDebugRegister[index].Dr7;
                ThreadDebugContextRemoveEntry(index);
            }

        }
    }

    return DllExchange.dNtContinue(ThreadContext, RaiseAlert);
}