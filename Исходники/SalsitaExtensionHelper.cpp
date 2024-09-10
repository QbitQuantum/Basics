void CSalsitaExtensionHelper::ResourcesDirGetDebugPath(const wchar_t *preprocessorDefinedPath, std::wstring &result)
{
  result.assign(preprocessorDefinedPath);
  std::replace(result.begin(), result.end(), L'/', L'\\');

  std::wstring canonicalized;
  canonicalized.resize(MAX_PATH+1);
  PathCanonicalizeW((LPWSTR)canonicalized.c_str(), result.c_str());
  result.assign(canonicalized.c_str());
  ResourcesDirNormalize(result);
}