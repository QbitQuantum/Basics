int CSVPToolBox::Explode(std::wstring szIn,
                         std::wstring szTok,
                         std::vector<std::wstring>* szaOut)
{
  szaOut->clear();

  std::wstring resToken;

  int size=sizeof(wchar_t);
  wchar_t* str = new wchar_t[szIn.length() + 1];
  wcscpy(str, szIn.c_str());
  wchar_t* sep = new wchar_t[szTok.length() + 1];
  wcscpy(sep, szTok.c_str());
  wchar_t* token = NULL;
  wchar_t* next_token = NULL;
  token = wcstok(str, sep, &next_token);

  while (token != NULL)
  {
    szaOut->push_back((std::wstring)token);
    token = wcstok( NULL, sep, &next_token);
  }

  delete[] str;
  delete[] sep;

  return 0;
}