/* [async] */ void  __stdcall EcDoAsyncWaitEx( 
    /* [in] */ PRPC_ASYNC_STATE EcDoAsyncWaitEx_AsyncHandle,
    /* [in] */ ACXH acxh,
    /* [in] */ unsigned long ulFlagsIn,
    /* [out] */ unsigned long *pulFlagsOut)
{

    NdrAsyncClientCall(
                      ( PMIDL_STUB_DESC  )&asyncemsmdb_StubDesc,
                      (PFORMAT_STRING) &MS2DOXCRPC__MIDL_ProcFormatString.Format[794],
                      ( unsigned char * )&EcDoAsyncWaitEx_AsyncHandle);
    
}