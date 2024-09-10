//----------------------------------------------------------------------------
//  
BOOL CAnchoBackgroundAPI::GetURL(CStringW & sURL)
{
  CString s;
  DWORD dwLength = INTERNET_MAX_URL_LENGTH;
  BOOL b = InternetCombineUrlW(m_sRootURL, sURL, s.GetBuffer(INTERNET_MAX_URL_LENGTH), &dwLength, 0);
  s.ReleaseBuffer();
  if (b)
  {
    sURL = s;
  }
  return b;
}