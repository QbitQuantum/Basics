NS_IMETHODIMP nsPrintSettingsWin::GetDriverName(char16_t **aDriverName)
{
  NS_ENSURE_ARG_POINTER(aDriverName);
  *aDriverName = mDriverName?reinterpret_cast<char16_t*>(wcsdup(mDriverName)):nullptr;
  return NS_OK;
}