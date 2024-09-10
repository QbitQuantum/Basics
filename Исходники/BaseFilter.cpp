STDMETHODIMP
BaseFilter::QueryFilterInfo(FILTER_INFO* aInfo)
{
  if (!aInfo)
    return E_POINTER;

  if (!mName.empty()) {
    StringCchCopyW(aInfo->achName, NUMELMS(aInfo->achName), mName.data());
  } else {
    aInfo->achName[0] = L'\0';
  }
  aInfo->pGraph = mGraph;
  NS_IF_ADDREF(mGraph);

  return S_OK;
}