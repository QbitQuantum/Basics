static void
CheckGRecord(const TCHAR *path)
{
  GRecord grecord;
  grecord.Initialize();
  ok1(grecord.VerifyGRecordInFile(Path(path), IgnoreError()));
}