VOID WINAPI RtlLeaveCriticalSection_ver0(__inout WND::LPCRITICAL_SECTION lpCriticalSection)
{
    if (lpCriticalSection == NULL)
    {
        int* ptr = reinterpret_cast<int*>(0x0);
        __try
        {
            // this will cause an exception
            *ptr = 17;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Exception in RtlLeaveCriticalSection replacement routine\n");
            fflush(stdout);
        }

        __try
        {
            volatile int i  = GenerateStackOverflow();
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            if(_resetstkoflw())
            {
                printf("Stack-Overflow in RtlLeaveCriticalSection replacement routine\n");
                fflush(stdout);
            }
        }
    }