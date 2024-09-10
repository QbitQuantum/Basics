BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
   TRACE("(%p, %u, %p) not fully implemented\n", (LPVOID)hinstDLL, fdwReason, lpvReserved);

   switch(fdwReason) {
      case DLL_PROCESS_ATTACH: {

         HKEY hKey;
         LONG r;

         DisableThreadLibraryCalls(hinstDLL);

         r = RegOpenKeyExW(HKEY_LOCAL_MACHINE, szPowerCfgSubKey, 0, KEY_READ | KEY_WRITE, &hKey);

         if (r != ERROR_SUCCESS) {
            TRACE("Couldn't open registry key HKLM\\%s, using some sane(?) defaults\n", debugstr_w(szPowerCfgSubKey));
         } else {
            BYTE lpValue[40];
            DWORD cbValue = sizeof(lpValue);
            r = RegQueryValueExW(hKey, szLastID, 0, 0, lpValue, &cbValue);
            if (r != ERROR_SUCCESS) {
               TRACE("Couldn't open registry entry HKLM\\%s\\LastID, using some sane(?) defaults\n", debugstr_w(szPowerCfgSubKey));
            }
            RegCloseKey(hKey);
         }

         PPRegSemaphore = CreateSemaphoreW(NULL, 1, 1, szSemaphoreName);
         if (PPRegSemaphore == (HANDLE)NULL) {
            ERR("Couldn't create Semaphore: %u\n", GetLastError());
            return FALSE;
         }
         break;
      }
      case DLL_PROCESS_DETACH:
         CloseHandle(PPRegSemaphore);
         break;
    }
    return TRUE;
}