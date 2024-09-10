//---------------------------------------------------------------------------
bool TFileZillaIntf::GetCurrentPath(wchar_t * Path, size_t MaxLen)
{
  CServerPath APath;
  bool Result = Check(FFileZillaApi->GetCurrentPath(APath), L"getcurrentpath");
  if (Result)
  {
    wcsncpy(Path, APath.GetPath(), MaxLen);
    Path[MaxLen - 1] = L'\0';
  }
  return Result;
}