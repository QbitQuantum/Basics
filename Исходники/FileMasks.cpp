//---------------------------------------------------------------------------
bool TFileCustomCommand::PatternReplacement(
  const UnicodeString & Pattern, UnicodeString & Replacement, bool & Delimit)
{
  // keep consistent with TSessionLog::OpenLogFile

  if (Pattern == L"!@")
  {
    Replacement = FData.HostName;
  }
  else if (AnsiSameText(Pattern, L"!u"))
  {
    Replacement = FData.UserName;
  }
  else if (AnsiSameText(Pattern, L"!p"))
  {
    Replacement = FData.Password;
  }
  else if (Pattern == L"!/")
  {
    Replacement = UnixIncludeTrailingBackslash(FPath);
  }
  else if (Pattern == L"!&")
  {
    Replacement = FFileList;
    // already delimited
    Delimit = false;
  }
  else
  {
    assert(Pattern.Length() == 1);
    Replacement = FFileName;
  }

  return true;
}