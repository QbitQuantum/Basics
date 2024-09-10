HRESULT
AddGraphToRunningObjectTable(IUnknown *aUnkGraph, DWORD *aOutRotRegister)
{
  HRESULT hr;

  nsRefPtr<IMoniker> moniker;
  nsRefPtr<IRunningObjectTable> runningObjectTable;

  hr = GetRunningObjectTable(0, getter_AddRefs(runningObjectTable));
  NS_ENSURE_TRUE(SUCCEEDED(hr), hr);

  const size_t STRING_LENGTH = 256;
  WCHAR wsz[STRING_LENGTH];

  StringCchPrintfW(wsz,
                   STRING_LENGTH,
                   L"FilterGraph %08x pid %08x",
                   (DWORD_PTR)aUnkGraph,
                   GetCurrentProcessId());

  hr = CreateItemMoniker(L"!", wsz, getter_AddRefs(moniker));
  NS_ENSURE_TRUE(SUCCEEDED(hr), hr);

  hr = runningObjectTable->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE,
                                    aUnkGraph,
                                    moniker,
                                    aOutRotRegister);
  NS_ENSURE_TRUE(SUCCEEDED(hr), hr);

  return S_OK;
}