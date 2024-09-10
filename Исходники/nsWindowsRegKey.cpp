NS_IMETHODIMP
nsWindowsRegKey::GetValueCount(uint32_t* aResult)
{
  if (NS_WARN_IF(!mKey)) {
    return NS_ERROR_NOT_INITIALIZED;
  }

  DWORD numValues;
  LONG rv = RegQueryInfoKeyW(mKey, nullptr, nullptr, nullptr, nullptr,
                             nullptr, nullptr, &numValues, nullptr, nullptr,
                             nullptr, nullptr);
  if (rv != ERROR_SUCCESS) {
    return NS_ERROR_FAILURE;
  }

  *aResult = numValues;
  return NS_OK;
}