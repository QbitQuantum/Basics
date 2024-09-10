/***********************************************************************
 *           I_RpcFreeBuffer [RPCRT4.@]
 *
 * Frees a buffer allocated by I_RpcGetBuffer or I_RpcReceive and unbinds from
 * the server interface.
 *
 * PARAMS
 *  pMsg [I/O] RPC message information.
 *
 * RETURNS
 *  RPC_S_OK.
 *
 * SEE ALSO
 *  I_RpcGetBuffer(), I_RpcReceive().
 */
RPC_STATUS WINAPI I_RpcFreeBuffer(PRPC_MESSAGE pMsg)
{
  RpcBinding* bind = (RpcBinding*)pMsg->Handle;

  FB_TRACE("> (%p) Buffer=%p\n", pMsg, pMsg->Buffer);

  if (!bind)
  {
    FE_ERR("< no binding\n");
    return RPC_S_INVALID_BINDING;
  }

  if (pMsg->ReservedForRuntime)
  {
    RpcConnection *conn = (RpcConnection *)pMsg->ReservedForRuntime;
    RPCRT4_CloseBinding(bind, conn);
    RPCRT4_ReleaseBinding(bind);
    pMsg->ReservedForRuntime = NULL;
  }
  I_RpcFree(pMsg->Buffer);

  FE_TRACE("< \n");
  return RPC_S_OK;
}