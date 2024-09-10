void MyRemoteProc( 
    /* [in] */ int param1,
    /* [out] */ int __RPC_FAR outArray[ 100 ])
{

    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&MyInterface_StubDesc,
                          0);
        
        
        
        _StubMsg.BufferLength = 4U;
        NdrNsGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, MyInterface__MIDL_AutoBindHandle );
        
        *(( int __RPC_FAR * )_StubMsg.Buffer)++ = param1;
        
        NdrNsSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer, (RPC_BINDING_HANDLE __RPC_FAR *) &MyInterface__MIDL_AutoBindHandle );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrFixedArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                 (unsigned char __RPC_FAR * __RPC_FAR *)&outArray,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2],
                                 (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}