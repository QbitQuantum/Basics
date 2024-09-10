static FILE *LocalOpenLogFile(UnicodeString LogFileName, TDateTime Started, TSessionData *SessionData, bool Append, UnicodeString &ANewFileName)
{
  UnicodeString NewFileName = StripPathQuotes(GetExpandedLogFileName(LogFileName, Started, SessionData));
  FILE *Result = _wfsopen(ApiPath(NewFileName).c_str(),
      Append ? L"ab" : L"wb", SH_DENYWR);
  if (Result != nullptr)
  {
    setvbuf(Result, nullptr, _IONBF, BUFSIZ);
    ANewFileName = NewFileName;
  }
  else
  {
    throw ECRTExtException(FMTLOAD(LOG_OPENERROR, NewFileName));
  }
  return Result;
}