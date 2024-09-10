auto_sz::auto_sz(const STRRET& sr, LPCITEMIDLIST piid)
  : m_sz(NULL)
  , m_bDelete(false)
  , m_nSize(0)
{
  switch (sr.uType)
  {
  case STRRET_CSTR:
    {
      size_t len = lstrlenA(sr.cStr)+1;
      Realloc(len);
      MultiByteToWideChar(CP_ACP, 0, sr.cStr, -1, *this, (int)len);
    }
    break;
  case STRRET_WSTR:
    operator=(sr.pOleStr);
    break;
  case STRRET_OFFSET:
    operator=((LPCWSTR)(&piid->mkid)+sr.uOffset);
    break;
  default:
    assert(0);
  }
}