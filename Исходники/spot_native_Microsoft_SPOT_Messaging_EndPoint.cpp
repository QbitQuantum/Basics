HRESULT Library_spot_native_Microsoft_SPOT_Messaging_EndPoint::SendMessageRaw___SZARRAY_U1__mscorlibSystemType__U4__I4__SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    NATIVE_PROFILE_CLR_MESSAGING();
    TINYCLR_HEADER();

    CLR_RT_HeapBlock*                           pThis;
    CLR_Messaging_Commands::Messaging_Send*     rpc;
    CLR_RT_HeapBlock_EndPoint::Message*         msg;
    CLR_RT_HeapBlock_EndPoint::Port             port;
    CLR_RT_HeapBlock_EndPoint*                  ep;
    CLR_INT64*                                  timeout;
    CLR_RT_HeapBlock_Array*                     pData;
    CLR_UINT32                                  len;
    bool                                        fRes;
    CLR_UINT32                                  seq;

    pThis = stack.This(); FAULT_ON_NULL(pThis);

    TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_EndPoint::ExtractInstance( pThis[ FIELD__m_handle ], ep ));

    if(CLR_RT_ReflectionDef_Index::Convert( stack.Arg1(), port.m_type ) == false) TINYCLR_SET_AND_LEAVE(CLR_E_NULL_REFERENCE);
    port.m_id = stack.Arg2().NumericByRefConst().u4;

    TINYCLR_CHECK_HRESULT(stack.SetupTimeout( stack.Arg3(), timeout ));

    pData = stack.Arg4().DereferenceArray(); FAULT_ON_NULL(pData);

    //Send message
    rpc = NULL;
    if(stack.m_customState == 1)
    {
        len = sizeof(CLR_RT_HeapBlock_EndPoint::Address) + pData->m_numOfElements;
        rpc = (CLR_Messaging_Commands::Messaging_Send*)CLR_RT_Memory::Allocate( len ); CHECK_ALLOCATION(rpc);

        rpc->m_addr.m_to   = port;
        rpc->m_addr.m_from = ep->m_addr;
        rpc->m_addr.m_seq  = ep->m_seq++;
        memcpy( rpc->m_data, pData->GetFirstElement(), pData->m_numOfElements );

        //Push sequence number onto the eval stack to wait for reply
        stack.PushValueI4( rpc->m_addr.m_seq );
        
        CLR_EE_MSG_EVENT_RPC( CLR_Messaging_Commands::c_Messaging_Send, len, rpc, WP_Flags::c_NonCritical );
        
        stack.m_customState = 2;
    }

    //get seq# from stack
    seq = stack.m_evalStack[ 1 ].NumericByRef().u4;

    fRes = true;
    msg  = NULL;

    while(fRes)
    {
        msg = ep->FindMessage( CLR_Messaging_Commands::c_Messaging_Reply, &seq );

        if(msg) break;

        TINYCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.WaitEvents( stack.m_owningThread, *timeout, CLR_RT_ExecutionEngine::c_Event_EndPoint, fRes ));
    }

    stack.PopValue();       //seq
    stack.PopValue();       //Timeout

    {
        CLR_RT_HeapBlock& top = stack.PushValueAndClear();

        if(msg)
        {
            TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance( top, msg->m_length, g_CLR_RT_WellKnownTypes.m_UInt8 ));

            memcpy( top.DereferenceArray()->GetFirstElement(), msg->m_data, msg->m_length );

            msg->Unlink(); CLR_RT_Memory::Release( msg );
        }
    }

    TINYCLR_NOCLEANUP();
}