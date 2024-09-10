void UnescapeUrl(std::wstring& url)
{
  try
  {
    DWORD result_length = INTERNET_MAX_URL_LENGTH;
    std::unique_ptr<wchar_t[]> result(new wchar_t[result_length]);
    HRESULT hr = UrlUnescapeW(const_cast<wchar_t*>(url.c_str()), result.get(), &result_length, 0);
    if (hr == S_OK)
    {
      url = std::wstring(result.get(), result_length);
    }
    /*
     * Do nothing. This masks error return values from UrlUnescape without logging the error.
     */
  }
  catch(std::bad_alloc e)
  {
    /*
     * When the code has a systematic way of handling bad_alloc, we'll rethrow (probably).
     * Until then, we mask the exception and make no modification.
     */
  }
  catch(...)
  {
    // no modification if any other exception
  }
}