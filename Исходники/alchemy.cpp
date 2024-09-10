STDAPI DllUnregisterServer(VOID)
#endif
{
   HRESULT rslt;

   HINSTANCE hInst;

   hInst = GetModuleHandle(DBCLIENT_DLL);
   if (hInst)
   {
      DBIPATH pszDllPath =
      {
         0
      };
      OLECHAR pszDllPathw[DBIMAXPATHLEN+1] =
      {
         0
      };
      GetModuleFileName(hInst, pszDllPath, sizeof(pszDllPath));
      MultiByteToWideChar(0, 0, pszDllPath, -1, pszDllPathw, sizeof(pszDllPathw)/sizeof(pszDllPathw[0]));

      ITypeLib *pTypeLib = 0; ; // oleauto.h
      rslt = LoadTypeLib(pszDllPathw, &pTypeLib);
      if (!rslt)
      {
         TLIBATTR *pLibAttr = 0; // oaidl.h
         pTypeLib->GetLibAttr(&pLibAttr);
         HRESULT hr = UnRegisterTypeLib(pLibAttr->guid, pLibAttr->wMajorVerNum, pLibAttr->wMinorVerNum, pLibAttr->lcid,
            pLibAttr->syskind);
         if (hr != S_OK)
         {
            regError("ERROR: UnregisterTypeLib returned %lX", hr);
         }

         pTypeLib->ReleaseTLibAttr(pLibAttr);
         pTypeLib->Release();
         pTypeLib = 0;
      }
      else
      {
         regError("ERROR: LoadTypeLib returned %lX", rslt);
      }
   }

#ifdef MIDAS_DLL
   // DSBASE
   rslt = Register_IF(NULL, PROGID_MDSBASE, NULL, PROGID_MDSBASE_1, NULL, CLSID_MDSBASE_1, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_MDSBASE_1, NULL, NULL, NULL, CLSID_MDSBASE_1, FALSE);

   // DSCursor
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_MDSCURSOR, NULL, PROGID_MDSCURSOR_1, NULL, CLSID_MDSCURSOR_1, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_MDSCURSOR_1, NULL, NULL, NULL, CLSID_MDSCURSOR_1, FALSE);

   // DSDATAPACKET
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_MDATAPACKETREAD, NULL, NULL, NULL, CLSID_MDATAPACKETREAD, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_MDATAPACKETWRITE, NULL, NULL, NULL, CLSID_MDATAPACKETWRITE, FALSE);
#else
   // DSBASE
   rslt = Register_IF(NULL, PROGID_DSBASE, NULL, PROGID_DSBASE_2, NULL, CLSID_DSBASE_2, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DSBASE_1, NULL, NULL, NULL, CLSID_DSBASE_1, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DSBASE_2, NULL, NULL, NULL, CLSID_DSBASE_2, FALSE);

   // DSCursor
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DSCURSOR, NULL, PROGID_DSCURSOR_2, NULL, CLSID_DSCURSOR_2, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DSCURSOR_1, NULL, NULL, NULL, CLSID_DSCURSOR_1, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DSCURSOR_2, NULL, NULL, NULL, CLSID_DSCURSOR_2, FALSE);

   // DSDATAPACKET
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DATAPACKETREAD, NULL, NULL, NULL, CLSID_DATAPACKETREAD, FALSE);
   if (!rslt)
      rslt = Register_IF(NULL, PROGID_DATAPACKETWRITE, NULL, NULL, NULL, CLSID_DATAPACKETWRITE, FALSE);
#endif
   return rslt;
}