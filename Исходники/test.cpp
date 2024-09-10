void main(int argc, char **argv)
{
  HMODULE hModUser32;
  HMODULE hModSecur32;

  hModUser32 = LoadLibrary("USER32.DLL");
  if (hModUser32 == NULL) exit(1);
  hModSecur32 = LoadLibrary("SECUR32.DLL");
  if (hModSecur32 == NULL) exit(1);  

#if 1  
  printf("cMonitors(real)=%d\n", GetSystemMetrics(SM_CMONITORS));
  Real_GetSystemMetrics = (LPGETSYSTEMMETRICS)NWHookCreate(GetProcAddress(hModUser32, "GetSystemMetrics"), Hook_GetSystemMetrics);
  printf("cMonitors(hook)=%d\n", GetSystemMetrics(SM_CMONITORS));
  NWHookDelete(Real_GetSystemMetrics);
#endif
  
  Real_EncryptMessage = (ENCRYPT_MESSAGE_FN)NWHookCreate(GetProcAddress(hModSecur32, "EncryptMessage"), Hook_EncryptMessage);
  EncryptMessage(NULL, 0, NULL, 0);
  NWHookDelete(Real_EncryptMessage);
  
  FreeLibrary(hModUser32);
  FreeLibrary(hModSecur32);
  
  exit(0);
}