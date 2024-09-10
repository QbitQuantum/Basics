/* [async] */ void  AsyncGet( 
    /* [in] */ PRPC_ASYNC_STATE AsyncGet_AsyncHandle,
    /* [in] */ handle_t IDL_handle,
    /* [out] */ long *pSize,
    /* [size_is][size_is][out] */ KeyValuePair **ppKvs)
{

    NdrAsyncClientCall(
                      ( PMIDL_STUB_DESC  )&AnInterface_StubDesc,
                      (PFORMAT_STRING) &interface1__MIDL_ProcFormatString.Format[92],
                      ( unsigned char * )&AsyncGet_AsyncHandle);
    
}