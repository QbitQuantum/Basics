void UnicodeString::Init(const wchar_t * Str, intptr_t Length)
{
  Data.resize(Length);
  if (Length > 0)
  {
    wmemmove(const_cast<wchar_t *>(Data.c_str()), Str, Length);
  }
  Data = Data.c_str();
}