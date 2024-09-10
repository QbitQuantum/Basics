static void RPCRT4_process_packet(RpcConnection* conn, RpcPktHdr* hdr, void* buf)
{
  RpcBinding* pbind;
  RPC_MESSAGE msg;
  RpcServerInterface* sif;
  RPC_DISPATCH_FUNCTION func;
  packet_state state;

  state.msg = &msg;
  state.buf = buf;
  TlsSetValue(worker_tls, &state);
  memset(&msg, 0, sizeof(msg));
  msg.BufferLength = hdr->len;
  msg.Buffer = buf;
  sif = RPCRT4_find_interface(&hdr->object, &hdr->if_id);
  if (sif) {
    TRACE("packet received for interface %s\n", debugstr_guid(&hdr->if_id));
    msg.RpcInterfaceInformation = sif->If;
    /* create temporary binding for dispatch */
    RPCRT4_MakeBinding(&pbind, conn);
    RPCRT4_SetBindingObject(pbind, &hdr->object);
    msg.Handle = (RPC_BINDING_HANDLE)pbind;
    /* process packet */
    switch (hdr->ptype) {
    case PKT_REQUEST:
      /* find dispatch function */
      msg.ProcNum = hdr->opnum;
      if (sif->Flags & RPC_IF_OLE) {
        /* native ole32 always gives us a dispatch table with a single entry
         * (I assume that's a wrapper for IRpcStubBuffer::Invoke) */
        func = *sif->If->DispatchTable->DispatchTable;
      } else {
        if (msg.ProcNum >= sif->If->DispatchTable->DispatchTableCount) {
          ERR("invalid procnum\n");
          func = NULL;
        }
        func = sif->If->DispatchTable->DispatchTable[msg.ProcNum];
      }

      /* put in the drep. FIXME: is this more universally applicable?
         perhaps we should move this outward... */
      msg.DataRepresentation = 
        MAKELONG( MAKEWORD(hdr->drep[0], hdr->drep[1]),
                  MAKEWORD(hdr->drep[2], 0));

      /* dispatch */
      __TRY {
        if (func) func(&msg);
      } __EXCEPT(rpc_filter) {
        /* failure packet was created in rpc_filter */
        TRACE("exception caught, returning failure packet\n");
      } __ENDTRY

      /* send response packet */
      I_RpcSend(&msg);
      break;
    default:
      ERR("unknown packet type\n");
      break;
    }

    RPCRT4_DestroyBinding(pbind);
    msg.Handle = 0;
    msg.RpcInterfaceInformation = NULL;
  }
  else {