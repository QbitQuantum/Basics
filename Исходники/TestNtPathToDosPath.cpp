void
DriveMapping::Disconnect(wchar_t aDriveLetter)
{
  wchar_t drvTemplate[] = {aDriveLetter, L':', L'\0'};
  DWORD result = WNetCancelConnection2W(drvTemplate, 0, TRUE);
  MOZ_ASSERT(result == NO_ERROR);
}