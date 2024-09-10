DWORD __stdcall NetrMessageNameEnum(
    /* [unique][string][in] */ MSGSVC_HANDLE ServerName,
    /* [out][in] */ LPMSG_ENUM_STRUCT InfoStruct,
    /* [in] */ DWORD PrefMaxLen,
    /* [out] */ LPDWORD TotalEntries,
    /* [unique][out][in] */ LPDWORD ResumeHandle)
{

    CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif

#if defined( _ALPHA_ )
    va_start(vlist,ResumeHandle);
    _RetVal = NdrClientCall(
                  ( PMIDL_STUB_DESC  )&msgsvc_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall(
                  ( PMIDL_STUB_DESC  )&msgsvc_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22],
                  ( unsigned char __RPC_FAR * )&ServerName,
                  ( unsigned char __RPC_FAR * )&InfoStruct,
                  ( unsigned char __RPC_FAR * )&PrefMaxLen,
                  ( unsigned char __RPC_FAR * )&TotalEntries,
                  ( unsigned char __RPC_FAR * )&ResumeHandle);
#else
    _RetVal = NdrClientCall(
                  ( PMIDL_STUB_DESC  )&msgsvc_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22],
                  ( unsigned char __RPC_FAR * )&ServerName);
#endif
    return ( DWORD  )_RetVal.Simple;

}