UnicodeString UpperCase(const UnicodeString & Str)
{
  std::wstring Result(Str.c_str(), Str.Length());
  // Result.SetLength(Str.Length());
  std::transform(Result.begin(), Result.end(), Result.begin(), ::toupper);
  return Result;
}