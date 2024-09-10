/***********************************************************************
 *           RpcSsDestroyClientContext
 */
void WINAPI RpcSsDestroyClientContext(void** ContextHandle)
{
  RPC_STATUS status;

  status = RpcSmDestroyClientContext(ContextHandle);

  if(status != RPC_S_OK) 
    RpcRaiseException(status);
}