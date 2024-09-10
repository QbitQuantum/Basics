LOCAL void* GetHostByAddrThread_Func(void* _HostInfo)
{
  sHostInfo *HostInfo = (sHostInfo *) _HostInfo;

  GetHostByAddr(HostInfo->HostMachineAddress, HostInfo->szHostMachineName);

  return 0;
}