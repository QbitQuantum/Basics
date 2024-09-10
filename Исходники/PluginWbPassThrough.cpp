ContentType WBPassthruSink::GetContentTypeFromURL(const std::wstring& src)
{
  std::wstring schemeAndHierarchicalPart = GetSchemeAndHierarchicalPart(src);
  auto contentType = GetContentTypeFromString(schemeAndHierarchicalPart);
  if (contentType == ContentType::CONTENT_TYPE_OTHER &&
    AdblockPlus::IE::InstalledMajorVersion() == 8)
  {
    std::wstring queryString = GetQueryString(src);
    wchar_t* nextToken = nullptr;
    const wchar_t* token = wcstok_s(&queryString[0], L"&=", &nextToken);
    while (token != nullptr)
    {
      contentType = GetContentTypeFromString(token);
      if (contentType != ContentType::CONTENT_TYPE_OTHER)
      {
         return contentType;
      }
      token = wcstok_s(nullptr, L"&=", &nextToken);
    }
  }
  return contentType;
}