static void
CheckTlbPath(JSONWriter& aJson, const nsAString& aTypelibPath)
{
  const nsString& flatPath = PromiseFlatString(aTypelibPath);
  DWORD bufCharLen = ExpandEnvironmentStrings(flatPath.get(), nullptr, 0);

  auto buf = MakeUnique<WCHAR[]>(bufCharLen);

  if (!ExpandEnvironmentStrings(flatPath.get(), buf.get(), bufCharLen)) {
    return;
  }

  // See whether this tlb can actually be loaded
  RefPtr<ITypeLib> typeLib;
  HRESULT hr = LoadTypeLibEx(buf.get(), REGKIND_NONE, getter_AddRefs(typeLib));

  nsPrintfCString loadResult("0x%08X", hr);
  aJson.StringProperty("LoadResult", loadResult.get());
}