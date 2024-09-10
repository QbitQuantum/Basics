LPWSTR CNktDvStackTrace::GetNearestSymbol(__in SIZE_T nDepth) const
{
  CNktDvStackTrace *lpThis = const_cast<CNktDvStackTrace*>(this);
  LPWSTR sW;

  sW = NULL;
  if (nDepth < NKT_DV_TMSG_ONHOOKCALLED_StackTraceDepth &&
      nStackTrace[nDepth] != 0)
  {
    CNktAutoFastMutex cLock(&(lpThis->GetLockObject()));
    LPWSTR szCopyW;
    SIZE_T nLen;
    HRESULT hRes;

    if (szSymbolW[nDepth] == NULL)
    {
      hRes = lpThis->InitExpFunc(nDepth);
      if (FAILED(hRes))
        return NULL;
      if (cExpFunc[nDepth] != NULL)
      {
        sW = cExpFunc[nDepth]->GetCompleteName();
      }
      else if (cMod[nDepth] != NULL)
      {
        sW = cMod[nDepth]->GetFileName();
      }
      else
      {
        sW = L"";
      }
      nLen = wcslen(sW) + 1;
      szCopyW = (LPWSTR)nktMemMalloc(nLen * sizeof(WCHAR));
      if (szCopyW == NULL)
        return NULL;
      nktMemCopy(szCopyW, sW, nLen * sizeof(WCHAR));
      _ReadWriteBarrier();
      lpThis->szSymbolW[nDepth] = szCopyW;
      _ReadWriteBarrier();
    }
    sW = szSymbolW[nDepth];
  }
  return sW;
}