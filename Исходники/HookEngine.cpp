    /**
    HookEngine_Memset

    memset without calling memset
    */
    __forceinline void HookEngine_Memset(LPVOID dst, BYTE set, SIZE_T length)
    {
        if (dst && length)
        {
            __stosb((unsigned char*)dst, set, length);
        }
    }