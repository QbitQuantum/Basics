/*
 * @implemented
 */
BOOL
WINAPI
Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
  MODULEENTRY32W me;
  BOOL Ret;

  CHECK_PARAM_SIZEA(lpme, sizeof(MODULEENTRY32));

  me.dwSize = sizeof(MODULEENTRY32W);

  Ret = Module32FirstW(hSnapshot, &me);
  if(Ret)
  {
    lpme->th32ModuleID = me.th32ModuleID;
    lpme->th32ProcessID = me.th32ProcessID;
    lpme->GlblcntUsage = me.GlblcntUsage;
    lpme->ProccntUsage = me.ProccntUsage;
    lpme->modBaseAddr = me.modBaseAddr;
    lpme->modBaseSize = me.modBaseSize;
    lpme->hModule = me.hModule;

    WideCharToMultiByte(CP_ACP, 0, me.szModule, -1, lpme->szModule, sizeof(lpme->szModule), 0, 0);
    WideCharToMultiByte(CP_ACP, 0, me.szExePath, -1, lpme->szExePath, sizeof(lpme->szExePath), 0, 0);
  }

  return Ret;
}