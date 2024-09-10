BOOL WINAPI FixPointer(__in LPENVIRONMENT lpEnv, __in LPVOID lpFunction, __in DWORD_PTR tag)
{
    BOOL bSuccess = FALSE;
    LPCWINAPI_TABLE lpTable = lpEnv->lpWinapiTable;
    LPBYTE lpDefWindowProcCaller = (LPBYTE)(lpFunction);
    for (ULONG i = 0; i < 0x40; ++i )
    {
        if (lpDefWindowProcCaller[i] == 0xc3) // ret
            break;
        if (lpDefWindowProcCaller[i] == 0xc2) // ret
            break;
        if (*(DWORD*)&lpDefWindowProcCaller[i] == tag)
        {
            DWORD dwOut;
            if (lpTable->VirtualProtect(&lpDefWindowProcCaller[i], sizeof(void*), PAGE_EXECUTE_READWRITE, &dwOut))
            {
                *(DWORD_PTR*)&lpDefWindowProcCaller[i] = (DWORD_PTR)lpEnv;
                bSuccess = TRUE;
                lpTable->VirtualProtect(&lpDefWindowProcCaller[i], sizeof(void*), dwOut, &dwOut);
            }
            break;
        }
    }
    return bSuccess;
}