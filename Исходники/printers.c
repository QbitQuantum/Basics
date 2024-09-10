wstring
printer_get_default(void)
{
  static wchar dp[99];
  DWORD len = sizeof dp;
  if (GetDefaultPrinterW(dp, &len))
    return dp;
  else
    return W("");
}