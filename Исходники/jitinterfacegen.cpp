void FixupInlineGetters(DWORD tlsSlot, const LPVOID * pLocations, int nLocations)
{
    BYTE* pInlineGetter;
    DWORD dwOldProtect;
    for (int i=0; i<nLocations; i++)
    {
        pInlineGetter = (BYTE*)GetEEFuncEntryPoint((BYTE*)pLocations[i]);

        static const DWORD cbPatch = 9;
        if (!ClrVirtualProtect(pInlineGetter, cbPatch, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        {
            ThrowLastError();
        }

        DWORD offset = (tlsSlot * sizeof(LPVOID) + offsetof(TEB, TlsSlots));

#if defined(_TARGET_AMD64_)
        // mov  r??, gs:[TLS offset]
        _ASSERTE_ALL_BUILDS("clr/src/VM/JITinterfaceGen.cpp",
                            pInlineGetter[0] == 0x65 &&
                            pInlineGetter[2] == 0x8B &&
                            pInlineGetter[4] == 0x25 &&
                            "Initialization failure while stomping instructions for the TLS slot offset: the instruction at the given offset did not match what we expect");

        *((DWORD*)(pInlineGetter + 5)) = offset;
#else // _TARGET_AMD64_
        PORTABILITY_ASSERT("FixupInlineGetters");
#endif //_TARGET_AMD64_

        FlushInstructionCache(GetCurrentProcess(), pInlineGetter, cbPatch);
        ClrVirtualProtect(pInlineGetter, cbPatch, dwOldProtect, &dwOldProtect);
    }
}