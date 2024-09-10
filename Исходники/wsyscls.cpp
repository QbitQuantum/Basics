TSystemTime::TSystemTime(const tstring& s, LCID locale)
{
  _USES_CONVERSION_A;
  LPCOLESTR olestr = _A2W_A(s.c_str());
  const LCID lcid = locale ? locale : GetUserDefaultLCID();
  const ULONG flags = 0;
  DATE date;
  HRESULT hr = VarDateFromStr(VARDATEFROMSTR_PARAM1(olestr), lcid, flags, &date);
  if (hr != S_OK) TXOwl::Raise(IDS_SYSTEMTIMEPARSEFAIL);
  int r = VariantTimeToSystemTime(date, this);
  if (r == FALSE) TXOwl::Raise(IDS_SYSTEMTIMEPARSEFAIL);
}