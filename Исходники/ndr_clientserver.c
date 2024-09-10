/***********************************************************************
 *           NdrFreeBuffer [RPCRT4.@]
 */
void WINAPI NdrFreeBuffer(PMIDL_STUB_MESSAGE pStubMsg)
{
  TRACE("(pStubMsg == ^%p)\n", pStubMsg);
  if (pStubMsg->fBufferValid)
  {
    I_RpcFreeBuffer(pStubMsg->RpcMsg);
    pStubMsg->fBufferValid = FALSE;
  }
}