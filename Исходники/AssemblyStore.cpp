HRESULT AssemblyStore::ReadFileToStream(LPCWSTR fileName, IStream* pStream) 
{
    HRESULT hr = SHCreateStreamOnFileEx
                    (fileName,
                     STGM_READ | STGM_SHARE_DENY_WRITE | STGM_FAILIFTHERE,
                     0, FALSE, NULL,
                     &pStream);
    return hr;
}