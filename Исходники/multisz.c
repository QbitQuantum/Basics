LONG
WINAPI
MultiSzQuery(
    PMULTI_SZ pMultiSz,
    HKEY hKey,
    LPCWSTR pwszValueName
    )
{
   LONG lResult;
   DWORD dwType, cbData;
   LPBYTE lpData;

   /* Initialize the MULTI_SZ. */
   MultiSzInit(pMultiSz);

   /* Compute the size of the value. */
   cbData = 0;
   lResult = RegQueryValueExW(
                hKey,
                pwszValueName,
                NULL,
                &dwType,
                NULL,
                &cbData
                );
   if (lResult != NO_ERROR)
   {
      return lResult;
   }
   if (dwType != REG_MULTI_SZ)
   {
      return ERROR_INVALID_DATA;
   }

   /* Allocate a buffer to hold the MULTI_SZ. */
   lpData = RadiusAlloc(cbData);

   /* Get the value. */
   lResult = RegQueryValueExW(
                hKey,
                pwszValueName,
                NULL,
                &dwType,
                lpData,
                &cbData
                );
   if (lResult != NO_ERROR)
   {
      RadiusFree(lpData);
      return lResult;
   }
   if (dwType != REG_MULTI_SZ)
   {
      RadiusFree(lpData);
      return ERROR_INVALID_DATA;
   }

   /* Store the result. */
   pMultiSz->pwszValue = (LPWSTR)lpData;
   pMultiSz->nChar = cbData / sizeof(WCHAR);

   return NO_ERROR;
}