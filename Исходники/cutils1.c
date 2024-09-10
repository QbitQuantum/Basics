VOID NEAR PASCAL WriteProfileInt(WORD wAppName, WORD wKey, int nVal)
{
   HANDLE hAppName, hKey;
   char buf[10];

   if(!(hAppName=MyLoadString(wAppName, NULL, LMEM_MOVEABLE)))
      goto Error1;
   if(!(hKey=MyLoadString(wKey, NULL, LMEM_MOVEABLE)))
      goto Error2;

   wsprintf(buf, "%d", nVal);
   WriteProfileString(LocalLock(hAppName), LocalLock(hKey), buf);

   LocalUnlock(hKey);
   LocalUnlock(hAppName);
Error2:
   LocalFree(hKey);
Error1:
   LocalFree(hAppName);
}