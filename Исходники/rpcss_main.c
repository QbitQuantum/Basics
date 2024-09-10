/* returns false if we discover at the last moment that we
   aren't ready to terminate */
BOOL RPCSS_Shutdown(void)
{
  RpcMgmtStopServerListening(NULL);
  RpcServerUnregisterIf(epm_v3_0_s_ifspec, NULL, TRUE);
  RpcServerUnregisterIf(Irot_v0_2_s_ifspec, NULL, TRUE);

  CloseHandle(exit_event);

  return TRUE;
}