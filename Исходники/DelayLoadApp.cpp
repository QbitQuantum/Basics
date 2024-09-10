void IsModuleLoaded(PCTSTR pszModuleName) {

   HMODULE hmod = GetModuleHandle(pszModuleName);
   char sz[100];
#ifdef UNICODE
   StringCchPrintfA(sz, _countof(sz), "Module \"%S\" is %Sloaded.", 
      pszModuleName, (hmod == NULL) ? L"not " : L"");
#else
   StringCchPrintfA(sz, _countof(sz), "Module \"%s\" is %sloaded.", 
      pszModuleName, (hmod == NULL) ? "not " : "");
#endif
   chMB(sz);
}