HRESULT CClsIdIidList::Remove(__in REFCLSID sClsId, __in REFIID sIid)
{
  CNktAutoFastMutex cLock(this);
  SIZE_T nIndex;

  if ((nIndex = Find(sClsId, sIid)) != NKT_SIZE_T_MAX)
  {
    memmove(lpList+nIndex, lpList+(nIndex+1), (nCount-nIndex-1)*sizeof(ITEM));
    nCount--;
    return S_OK;
  }
  return S_FALSE;
}