/* add this function to hellop.c */
void HavokShutdown(void)
{
    RPC_STATUS status;

    status = RpcMgmtStopServerListening(NULL);

    if (status)
      return;

    status = RpcServerUnregisterIf(NULL, NULL, FALSE);

    if (status)
      return;

    return;
} //end Shutdown