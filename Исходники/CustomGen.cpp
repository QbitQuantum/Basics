std::wstring
MakeWideString(const char* input)
{
  wchar_t* tmp;
  size_t l = strlen(input);
  tmp = new wchar_t[l + 1];
  memset(tmp, 0, (l + 1) * sizeof(wchar_t));
  const char* mbr = input;
  mbsrtowcs(tmp, &mbr, l, NULL);
  std::wstring str(tmp);
  delete [] tmp;

  return str;
}