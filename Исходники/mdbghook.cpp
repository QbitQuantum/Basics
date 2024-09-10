/***
*_CRT_DUMP_CLIENT_M _CrtSetDumpClient() - set client dump hook
*
*Purpose:
*       set client dump hook
*
*Entry:
*       _CRT_DUMP_CLIENT_M pfnNewHook - new dump hook
*
*Exit:
*       return previous hook
*
*Exceptions:
*
*******************************************************************************/
_MRTIMP _CRT_DUMP_CLIENT_M __cdecl _CrtSetDumpClient
(
    _CRT_DUMP_CLIENT_M pfnNewHook
)
{
    if(_atexit_m_appdomain(_CrtDumpClient_managed_cleanup)!=0)
    {
        return NULL;
    }

    _CRT_DUMP_CLIENT_M pfnOldHook = (_CRT_DUMP_CLIENT_M) DecodePointer(__pfnDumpClientManaged);
    if (pfnNewHook)
    {
        __pfnDumpClientManaged = (_CRT_DUMP_CLIENT_M) EncodePointer(pfnNewHook);
        _CrtSetDumpClient((_CRT_DUMP_CLIENT)_CrtDumpClient_managed_thunk);
    }
    else
    {
        _CRT_DUMP_CLIENT_M enull = (_CRT_DUMP_CLIENT_M) EncodePointer(NULL)();
        __pfnDumpClientManaged = enull;
        _CrtSetDumpClient((_CRT_DUMP_CLIENT)NULL);
    }
    return pfnOldHook;
}