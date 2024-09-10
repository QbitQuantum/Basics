nsresult nsCollationWin::AllocateRawSortKey(PRInt32 strength, 
                                            const nsAString& stringIn, PRUint8** key, PRUint32* outLen)
{
  int byteLen;
  void *buffer;
  nsresult res = NS_OK;
  DWORD dwMapFlags = LCMAP_SORTKEY;

  if (strength == kCollationCaseInSensitive)
    dwMapFlags |= NORM_IGNORECASE;

  byteLen = LCMapStringW(mLCID, dwMapFlags, 
                         (LPCWSTR) PromiseFlatString(stringIn).get(),
                         -1, NULL, 0);
  buffer = PR_Malloc(byteLen);
  if (!buffer) {
    res = NS_ERROR_OUT_OF_MEMORY;
  } else {
    *key = (PRUint8 *)buffer;
    *outLen = LCMapStringW(mLCID, dwMapFlags, 
                           (LPCWSTR) PromiseFlatString(stringIn).get(),
                           -1, (LPWSTR) buffer, byteLen);
  }
  return res;
}