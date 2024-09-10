bool TopMenuCore::startup()
{
   SetLastError(ERROR_SUCCESS);
   DWORD le;

   if(!m_hStopEvent) {
      note("could not create stop event");
      return false;
   }
   
   char szLibPath[MAX_PATH];
   if(!GetModuleFileName((HINSTANCE)&__ImageBase, szLibPath, MAX_PATH)) {
      le = GetLastError();
      return false;
   }

   char szLibDrive[MAX_PATH];
   char szLibDir[MAX_PATH];
   char szLibFname[MAX_PATH];
   char szLibExt[MAX_PATH];
   _splitpath_s(szLibPath, szLibDrive, szLibDir, szLibFname, szLibExt); //lint !e534 JLD
   _makepath_s(szLibPath, szLibDrive, szLibDir, "*", "dll"); //lint !e534 JLD
   
   WIN32_FIND_DATA findData;
   HANDLE hSearch = FindFirstFile(szLibPath, &findData);
   if(hSearch) {
      do 
      {
         char szPath[MAX_PATH];
         _makepath_s(szPath, szLibDrive, szLibDir, findData.cFileName, ""); //lint !e534 JLD

         HMODULE hPluginMod = LoadLibrary(szPath);
         if(!hPluginMod) {
            le = GetLastError();
            continue;
         }

         FARPROC createProc = GetProcAddress(hPluginMod, CREATE_PROC_NAME);
         if(!createProc) {
            le = GetLastError();
            FreeLibrary(hPluginMod); //lint !e534 JLD
            continue;
         }

         FARPROC versionProc = GetProcAddress(hPluginMod, VERSION_PROC_NAME);
         if(!versionProc) {
            le = GetLastError();
            FreeLibrary(hPluginMod); //lint !e534 JLD
            continue;
         }
         
         TopMenu_PluginStackEntry* pStackPtr = m_pTopEntry;
         while(pStackPtr) {
            if(pStackPtr->m_hModule == hPluginMod) {
               break; // module already in stack
            }
         }
         if(pStackPtr) {
            FreeLibrary(hPluginMod); //lint !e534 JLD
            continue; // plugin already loaded
         }
      
         VERSION_PROC& GetPluginVersion = (VERSION_PROC&)*versionProc;
         DWORD pluginVersion = GetPluginVersion();
         if(pluginVersion < TopMenu_Plugin::GetPluginVersion()) {
            le = GetLastError();
            FreeLibrary(hPluginMod); //lint !e534 JLD
            continue;
         }

         CREATE_PROC& CreatePlugin = (CREATE_PROC&)*createProc;
         TopMenu_Plugin* pPlugin = CreatePlugin();
         if(!pPlugin) {
            le = GetLastError();
            FreeLibrary(hPluginMod); //lint !e534 JLD
            continue;
         }

         TopMenu_PluginStackEntry* pPluginEntry = new TopMenu_PluginStackEntry();
         pPluginEntry->m_hModule = hPluginMod;
         pPluginEntry->m_pPlugin = pPlugin;
         if(m_pTopEntry) {
            pPluginEntry->m_pNext = m_pTopEntry;
         }
         m_pTopEntry = pPluginEntry;
      } while(FindNextFile(hSearch, &findData));

      FindClose(hSearch); //lint !e534 JLD
      hSearch = NULL;
   }

   return true;
} //lint !e550 JLD