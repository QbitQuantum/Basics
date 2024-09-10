static HRESULT LoadUnknownMetadata(IStream *input, const GUID *preferred_vendor,
    DWORD persist_options, MetadataItem **items, DWORD *item_count)
{
    HRESULT hr;
    MetadataItem *result;
    STATSTG stat;
    BYTE *data;
    ULONG bytesread;

    TRACE("\n");

    hr = IStream_Stat(input, &stat, STATFLAG_NONAME);
    if (FAILED(hr))
        return hr;

    data = HeapAlloc(GetProcessHeap(), 0, stat.cbSize.QuadPart);
    if (!data) return E_OUTOFMEMORY;

    hr = IStream_Read(input, data, stat.cbSize.QuadPart, &bytesread);
    if (bytesread != stat.cbSize.QuadPart) hr = E_FAIL;
    if (hr != S_OK)
    {
        HeapFree(GetProcessHeap(), 0, data);
        return hr;
    }

    result = HeapAlloc(GetProcessHeap(), 0, sizeof(MetadataItem));
    if (!result)
    {
        HeapFree(GetProcessHeap(), 0, data);
        return E_OUTOFMEMORY;
    }

    PropVariantInit(&result[0].schema);
    PropVariantInit(&result[0].id);
    PropVariantInit(&result[0].value);

    result[0].value.vt = VT_BLOB;
    result[0].value.u.blob.cbSize = bytesread;
    result[0].value.u.blob.pBlobData = data;

    *items = result;
    *item_count = 1;

    return S_OK;
}