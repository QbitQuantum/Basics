 int PutData(const char* szKey, const void* pData, size_t nData)
 {
     USES_CONVERSION;
     int nResult = 0;
     void*   pProtectedData = NULL;
     size_t  nProtectedData = 0;
     {
         nResult = ProtectDataCAPI(
                         szKey,
                         pData,
                         nData,
                         &pProtectedData,
                         &nProtectedData);
         if(nResult)
             goto onCleanup;
         CRegKey key;
         if(pData)
         {
             nResult = key.Create(
                     HKEY_LOCAL_MACHINE,
                     c_szRegKeyName,
                     REG_NONE,
                     REG_OPTION_NON_VOLATILE,
                     KEY_WRITE|KEY_READ,
                     NULL,
                     NULL);
             if(nResult)
                 goto onCleanup;
             nResult = RegSetValueEx(
                         key,
                         A2CT(szKey),
                         NULL,
                         REG_BINARY,
                         (CONST BYTE*)pProtectedData,
                         nProtectedData);
             if(nResult)
                 goto onCleanup;
         }
         else
         {
             RegDeleteKey(HKEY_LOCAL_MACHINE, c_szRegKeyName);
         };
     };
 onCleanup:
     Free(pProtectedData, nProtectedData);
     return nResult;
 };