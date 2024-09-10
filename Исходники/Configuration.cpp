//---------------------------------------------------------------------------
UnicodeString TConfiguration::TrimVersion(const UnicodeString & Version) const
{
  UnicodeString Result = Version;
  while ((Result.Pos(L".") != Result.LastDelimiter(L".")) &&
    (Result.SubString(Result.Length() - 1, 2) == L".0"))
  {
    Result.SetLength(Result.Length() - 2);
  }
  return Result;
}