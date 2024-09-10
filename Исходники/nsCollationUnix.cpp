nsresult nsCollationUnix::AllocateRawSortKey(int32_t strength, 
                                             const nsAString& stringIn,
                                             uint8_t** key, uint32_t* outLen)
{
  nsresult res = NS_OK;

  nsAutoString stringNormalized;
  if (strength != kCollationCaseSensitive) {
    res = mCollation->NormalizeString(stringIn, stringNormalized);
    if (NS_FAILED(res))
      return res;
  } else {
    stringNormalized = stringIn;
  }
  // convert unicode to charset
  char *str;

  res = mCollation->UnicodeToChar(stringNormalized, &str);
  if (NS_SUCCEEDED(res) && str) {
    DoSetLocale();
    // call strxfrm to generate a key 
    size_t len = strxfrm(nullptr, str, 0) + 1;
    void *buffer = PR_Malloc(len);
    if (!buffer) {
      res = NS_ERROR_OUT_OF_MEMORY;
    } else if (strxfrm((char *)buffer, str, len) >= len) {
      PR_Free(buffer);
      res = NS_ERROR_FAILURE;
    } else {
      *key = (uint8_t *)buffer;
      *outLen = len;
    }
    DoRestoreLocale();
    PR_Free(str);
  }

  return res;
}