bool VSSClient::GetShadowPathW(const wchar_t *szFilePath, wchar_t *szShadowPath, int nBuflen)
{
   if (!m_bBackupIsInitialized)
      return false;

   /* check for valid pathname */
   bool bIsValidName;

   bIsValidName = wcslen(szFilePath) > 3;
   if (bIsValidName)
      bIsValidName &= iswalpha (szFilePath[0]) &&
                      szFilePath[1]==':' &&
                      szFilePath[2] == '\\';

   if (bIsValidName) {
      int nDriveIndex = towupper(szFilePath[0])-'A';
      if (m_szShadowCopyName[nDriveIndex][0] != 0) {
         wcsncpy(szShadowPath, m_szShadowCopyName[nDriveIndex], nBuflen);
         nBuflen -= (int)wcslen(m_szShadowCopyName[nDriveIndex]);
         wcsncat(szShadowPath, szFilePath+2, nBuflen);
         return true;
      }
   }

   wcsncpy(szShadowPath, szFilePath, nBuflen);
   errno = EINVAL;
   return false;
}