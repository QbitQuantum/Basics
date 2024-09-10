// plugin.getVariable("$MyVariable"); - get a Torque 3D console variable
STDMETHODIMP CIEWebGameCtrl::getVariable(BSTR name, BSTR* value)
{
	std::wstring wstr;
	std::string sstr;
	const char* astr;

	wstr.assign(name);
	sstr = WebCommon::WStringToString(wstr);
	astr = sstr.c_str();

   const char* avalue = NULL;
   char vinfo[256];
   vinfo[0] = 0;

   // requesting the version information
   if (!_stricmp(astr, "$version"))
   {
      char plugin[4096];

      GetModuleFileNameA(WebCommon::gPluginModule, plugin, 4096);
      DWORD dwHandle = 0;
      DWORD dwSize = GetFileVersionInfoSizeA(plugin, &dwHandle);
      if (dwSize >= 0)
      {
         LPBYTE lpInfo = new BYTE[dwSize];
         ZeroMemory(lpInfo, dwSize);
         if(GetFileVersionInfoA(plugin, 0, dwSize, lpInfo))
         {
            UINT valLen = MAX_PATH;
            LPVOID valPtr = NULL;
            if(::VerQueryValue(lpInfo, 
               TEXT("\\"),
               &valPtr,
               &valLen))
            {
               VS_FIXEDFILEINFO* pFinfo = (VS_FIXEDFILEINFO*)valPtr;

               sprintf(vinfo, "%i.%i", (pFinfo->dwProductVersionMS >> 16) & 0xFF, (pFinfo->dwFileVersionMS) & 0xFF);

            }