LONG
Win32U_RegUnLoadKey(HKEY keyName,   // IN:
                    LPCSTR subKey)  // IN:
{
   LONG ret;
   utf16_t *subKeyW = Unicode_GetAllocUTF16(subKey);

   ret = RegUnLoadKeyW(keyName, subKeyW);
   free(subKeyW);

   return ret;
}