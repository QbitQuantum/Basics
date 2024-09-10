/*************************************************************************
 * SHOpenRegStreamW	[SHLWAPI.@]
 *
 * See SHOpenRegStreamA.
 */
IStream * WINAPI SHOpenRegStreamW(HKEY hkey, LPCWSTR pszSubkey,
                                  LPCWSTR pszValue, DWORD dwMode)
{
  IStream *iStream;

  TRACE("(%p,%s,%s,0x%08x)\n", hkey, debugstr_w(pszSubkey),
        debugstr_w(pszValue), dwMode);
  iStream = SHOpenRegStream2W(hkey, pszSubkey, pszValue, dwMode);
  return iStream ? iStream : &rsDummyRegStream.IStream_iface;
}