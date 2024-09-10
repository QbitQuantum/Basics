static PVOID
get_module_base (void)
{
  PSYSTEM_MODULE_INFORMATION_ENTRY pModuleBase;
  PSYSTEM_MODULE_INFORMATION pModuleInfo;
  DWORD i, num_modules, status, rlen;
  PVOID result;

  status = NtQuerySystemInformation (SystemModuleInformation, NULL, 0, 
&rlen);
  if (status != STATUS_INFO_LENGTH_MISMATCH)
    {
      fprintf (stderr, "* NtQuerySystemInformation failed, 0x%08X\n", 
status);
      exit (EXIT_FAILURE);
    }

  pModuleInfo = (PSYSTEM_MODULE_INFORMATION) HeapAlloc (GetProcessHeap 
(), HEAP_ZERO_MEMORY, rlen);

  status = NtQuerySystemInformation (SystemModuleInformation, 
pModuleInfo, rlen, &rlen);
  if (status != STATUS_SUCCESS)
    {
      fprintf (stderr, "* NtQuerySystemInformation failed, 0x%08X\n", 
status);
      exit (EXIT_FAILURE);
    }

  num_modules = pModuleInfo->Count;
  pModuleBase = &pModuleInfo->Module[0];
  result = NULL;

  for (i = 0; i < num_modules; i++, pModuleBase++)
    if (strstr (pModuleBase->ImageName, "IPSECDRV.sys"))
      {
        result = pModuleBase->Base;
        break;
      }

  HeapFree (GetProcessHeap (), HEAP_NO_SERIALIZE, pModuleInfo);

  return (result);
}