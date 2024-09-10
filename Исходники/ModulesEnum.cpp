HRESULT CNktDvModulesEnumerator::MarkModuleAsDirty(__in HINSTANCE hDll)
{
  CNktAutoFastMutex cLock(&GetLockObject());
  SIZE_T i, nCount;

  nCount = sDirtyModules.aList.GetCount();
  for (i=0; i<nCount; i++)
  {
    if (sDirtyModules.aList[i] == hDll)
      return S_OK;
  }
  if (sDirtyModules.aList.AddElement(hDll) == FALSE)
    return E_OUTOFMEMORY;
  NktInterlockedExchange(&(sDirtyModules.nDoCheck), 1);
  return S_OK;
}