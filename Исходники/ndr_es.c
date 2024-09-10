/***********************************************************************
 *            NdrMesProcEncodeDecode [RPCRT4.@]
 */
void WINAPIV NdrMesProcEncodeDecode(handle_t Handle, const MIDL_STUB_DESC * pStubDesc, PFORMAT_STRING pFormat, ...)
{
    /* pointer to start of stack where arguments start */
    RPC_MESSAGE rpcMsg;
    MIDL_ES_MESSAGE *pEsMsg = Handle;
    /* size of stack */
    unsigned short stack_size;
    /* header for procedure string */
    const NDR_PROC_HEADER *pProcHeader = (const NDR_PROC_HEADER *)&pFormat[0];
    const RPC_CLIENT_INTERFACE *client_interface;
    __ms_va_list args;
    unsigned int number_of_params;
    ULONG_PTR arg_buffer[256];

    TRACE("Handle %p, pStubDesc %p, pFormat %p, ...\n", Handle, pStubDesc, pFormat);

    /* Later NDR language versions probably won't be backwards compatible */
    if (pStubDesc->Version > 0x50002)
    {
        FIXME("Incompatible stub description version: 0x%x\n", pStubDesc->Version);
        RpcRaiseException(RPC_X_WRONG_STUB_VERSION);
    }

    client_interface = pStubDesc->RpcInterfaceInformation;
    pEsMsg->InterfaceId = client_interface->InterfaceId;

    if (pProcHeader->Oi_flags & RPC_FC_PROC_OIF_RPCFLAGS)
    {
        const NDR_PROC_HEADER_RPC *header_rpc = (const NDR_PROC_HEADER_RPC *)&pFormat[0];
        stack_size = header_rpc->stack_size;
        pEsMsg->ProcNumber = header_rpc->proc_num;
        pFormat += sizeof(NDR_PROC_HEADER_RPC);
    }
    else
    {
        stack_size = pProcHeader->stack_size;
        pEsMsg->ProcNumber = pProcHeader->proc_num;
        pFormat += sizeof(NDR_PROC_HEADER);
    }

    if (pProcHeader->handle_type == RPC_FC_BIND_EXPLICIT)
    {
        switch (*pFormat) /* handle_type */
        {
        case RPC_FC_BIND_PRIMITIVE: /* explicit primitive */
            pFormat += sizeof(NDR_EHD_PRIMITIVE);
            break;
        case RPC_FC_BIND_GENERIC: /* explicit generic */
            pFormat += sizeof(NDR_EHD_GENERIC);
            break;
        case RPC_FC_BIND_CONTEXT: /* explicit context */
            pFormat += sizeof(NDR_EHD_CONTEXT);
            break;
        default:
            ERR("bad explicit binding handle type (0x%02x)\n", pProcHeader->handle_type);
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
        }
    }

    TRACE("stack size: 0x%x\n", stack_size);
    TRACE("proc num: %d\n", pEsMsg->ProcNumber);

    memset(&rpcMsg, 0, sizeof(rpcMsg));
    pEsMsg->StubMsg.RpcMsg = &rpcMsg;
    pEsMsg->StubMsg.StubDesc = pStubDesc;
    pEsMsg->StubMsg.pfnAllocate = pStubDesc->pfnAllocate;
    pEsMsg->StubMsg.pfnFree = pStubDesc->pfnFree;

    /* create the full pointer translation tables, if requested */
    if (pProcHeader->Oi_flags & RPC_FC_PROC_OIF_FULLPTR)
        pEsMsg->StubMsg.FullPtrXlatTables = NdrFullPointerXlatInit(0,XLAT_CLIENT);

    TRACE("Oi_flags = 0x%02x\n", pProcHeader->Oi_flags);
    TRACE("stubdesc version = 0x%x\n", pStubDesc->Version);
    TRACE("MIDL stub version = 0x%x\n", pStubDesc->MIDLVersion);

    /* needed for conformance of top-level objects */
    __ms_va_start( args, pFormat );
    pEsMsg->StubMsg.StackTop = va_arg( args, unsigned char * );
    __ms_va_end( args );

    pFormat = convert_old_args( &pEsMsg->StubMsg, pFormat, stack_size, FALSE,
                                arg_buffer, sizeof(arg_buffer), &number_of_params );

    switch (pEsMsg->Operation)
    {
    case MES_ENCODE:
        pEsMsg->StubMsg.BufferLength = mes_proc_header_buffer_size();

        client_do_args( &pEsMsg->StubMsg, pFormat, STUBLESS_CALCSIZE, NULL, number_of_params, NULL );

        pEsMsg->ByteCount = pEsMsg->StubMsg.BufferLength - mes_proc_header_buffer_size();
        es_data_alloc(pEsMsg, pEsMsg->StubMsg.BufferLength);

        mes_proc_header_marshal(pEsMsg);

        client_do_args( &pEsMsg->StubMsg, pFormat, STUBLESS_MARSHAL, NULL, number_of_params, NULL );

        es_data_write(pEsMsg, pEsMsg->ByteCount);
        break;
    case MES_DECODE:
        mes_proc_header_unmarshal(pEsMsg);

        es_data_read(pEsMsg, pEsMsg->ByteCount);

        client_do_args( &pEsMsg->StubMsg, pFormat, STUBLESS_UNMARSHAL, NULL, number_of_params, NULL );
        break;
    default:
        RpcRaiseException(RPC_S_INTERNAL_ERROR);
        return;
    }
    /* free the full pointer translation tables */
    if (pProcHeader->Oi_flags & RPC_FC_PROC_OIF_FULLPTR)
        NdrFullPointerXlatFree(pEsMsg->StubMsg.FullPtrXlatTables);
}