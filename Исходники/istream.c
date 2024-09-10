/*************************************************************************
 * @       [SHLWAPI.212]
 *
 * Call IStream_Write() on a stream.
 *
 * PARAMS
 *  lpStream [I] IStream object
 *  lpvSrc   [I] Source for data to write
 *  ulSize   [I] Size of data
 *
 * RETURNS
 *  Success: S_OK. ulSize bytes have been written to the stream from lpvSrc.
 *  Failure: An HRESULT error code, or E_FAIL if the write succeeded but the
 *           number of bytes written does not match.
 */
HRESULT WINAPI SHIStream_Write(IStream *lpStream, LPCVOID lpvSrc, ULONG ulSize)
{
  ULONG ulWritten;
  HRESULT hRet;

  TRACE("(%p,%p,%d)\n", lpStream, lpvSrc, ulSize);

  hRet = IStream_Write(lpStream, lpvSrc, ulSize, &ulWritten);

  if (SUCCEEDED(hRet) && ulWritten != ulSize)
    hRet = E_FAIL;

  return hRet;
}