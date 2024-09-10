HRESULT BstrStream::ReadBstr(BSTR *bstr)
{
    *bstr = SysAllocStringByteLen(NULL, avail());
    UINT nlen = SysStringByteLen(*bstr);

    ULONG read = 0, pos = 0, cb = nlen;
    HRESULT hr;

    LPBYTE pbuf = (LPBYTE)*bstr;
    for ( ; pos < nlen; cb -= read, pos += read) {
        hr = Read(&pbuf[pos], cb, &read);
        if (FAILED(hr)) {
            SysFreeString(*bstr);
            return hr;
        }
        if (read == 0) break;
    }

    return S_OK;
}