void CtxHello(
    /* [in] */ PCTXTYPE phContext)
{

    RPC_BINDING_HANDLE _Handle	=	0;

    RPC_MESSAGE _RpcMessage;

    MIDL_STUB_MESSAGE _StubMsg;

    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&hello_StubDesc,
                          1);


        if(phContext != 0)
            {
            _Handle = NDRCContextBinding(( NDR_CCONTEXT  )phContext);;

            }
        else
            {
            RpcRaiseException(RPC_X_SS_IN_NULL_CONTEXT);
            }

        _StubMsg.BufferLength = 20U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );

        NdrClientContextMarshall(
                            ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                            ( NDR_CCONTEXT  )phContext,
                            1);
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );

        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );

        }
    RpcEndFinally

}