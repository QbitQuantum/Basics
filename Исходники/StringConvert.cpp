AString UnicodeStringToMultiByte(const UString &srcString, UINT codePage)
{
  AString resultString;
  if(!srcString.IsEmpty())
  {
    int numRequiredBytes = srcString.Length() * 2;
    int numChars = WideCharToMultiByte(codePage, 0, srcString, 
      srcString.Length(), resultString.GetBuffer(numRequiredBytes), 
      numRequiredBytes + 1, NULL, NULL);
    #ifndef _WIN32_WCE
    if(numChars == 0)
      throw 282229;
    #endif
    resultString.ReleaseBuffer(numChars);
  }
  return resultString;
}