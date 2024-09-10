uint32_t GetModuleBase(DWORD procId, char* modName)
{
  HANDLE snapshot;
  MODULEENTRY32 modInfo;
  snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);
  modInfo.dwSize = sizeof(MODULEENTRY32);

  if (Module32First(snapshot, &modInfo))
  {
    // printf("mod %s\n", modInfo.szModule);
    if (!strcmp(modInfo.szModule, modName))
    {
      CloseHandle(snapshot);
      return (uint32_t)modInfo.modBaseAddr;
    }

    while (Module32Next(snapshot, &modInfo))
    {
      // printf("mod %s\n", modInfo.szModule);
      if (!strcmp(modInfo.szModule, modName))
      {
        CloseHandle(snapshot);
        return (uint32_t)modInfo.modBaseAddr;
      }
    }
  }
  CloseHandle(snapshot);
  return 0;
}