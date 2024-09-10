/* [async] */ void  AsyncFunc( 
    /* [in] */ PRPC_ASYNC_STATE AsyncFunc_AsyncHandle,
    /* [in] */ TRANS_HANDLE hTr)
{

    NdrAsyncClientCall(
                      ( PMIDL_STUB_DESC  )&InterfaceName_StubDesc,
                      (PFORMAT_STRING) &interface__MIDL_ProcFormatString.Format[388],
                      ( unsigned char * )&AsyncFunc_AsyncHandle);
    
}