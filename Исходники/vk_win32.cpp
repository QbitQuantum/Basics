bool ProcessImplicitLayersKey(HKEY key, const std::wstring &path,
                              std::vector<std::string> *otherJSONs, bool deleteOthers)
{
  bool thisRegistered = false;

  wchar_t name[1024] = {};
  DWORD nameSize = 1024;
  DWORD idx = 0;

  LONG ret = RegEnumValueW(key, idx++, name, &nameSize, NULL, NULL, NULL, NULL);

  std::wstring myJSON = path;
  for(size_t i = 0; i < myJSON.size(); i++)
    myJSON[i] = towlower(myJSON[i]);

  while(ret == ERROR_SUCCESS)
  {
    // convert the name here so we preserve casing
    std::string utf8name = StringFormat::Wide2UTF8(name);

    for(DWORD i = 0; i <= nameSize && name[i]; i++)
      name[i] = towlower(name[i]);

    if(wcscmp(name, myJSON.c_str()) == 0)
    {
      thisRegistered = true;
    }
    else if(wcsstr(name, L"renderdoc.json") != NULL)
    {
      if(otherJSONs)
        otherJSONs->push_back(utf8name);

      if(deleteOthers)
        RegDeleteValueW(key, name);
    }

    nameSize = 1024;
    ret = RegEnumValueW(key, idx++, name, &nameSize, NULL, NULL, NULL, NULL);
  }

  return thisRegistered;
}