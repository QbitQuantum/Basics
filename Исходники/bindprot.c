static HRESULT WINAPI ProtocolSinkHandler_ReportData(IInternetProtocolSink *iface,
        DWORD bscf, ULONG progress, ULONG progress_max)
{
    BindProtocol *This = impl_from_IInternetProtocolSinkHandler(iface);

    TRACE("(%p)->(%x %u %u)\n", This, bscf, progress, progress_max);

    This->bscf = bscf;
    This->progress = progress;
    This->progress_max = progress_max;

    if(!This->protocol_sink)
        return S_OK;

    if((This->pi & PI_MIMEVERIFICATION) && !This->reported_mime) {
        BYTE buf[BUFFER_SIZE];
        DWORD read = 0;
        LPWSTR mime;
        HRESULT hres;

        do {
            read = 0;
            if(is_apartment_thread(This))
                This->continue_call++;
            hres = IInternetProtocol_Read(This->protocol, buf,
                    sizeof(buf)-This->buf_size, &read);
            if(is_apartment_thread(This))
                This->continue_call--;
            if(FAILED(hres) && hres != E_PENDING)
                return hres;

            if(!This->buf) {
                This->buf = heap_alloc(BUFFER_SIZE);
                if(!This->buf)
                    return E_OUTOFMEMORY;
            }else if(read + This->buf_size > BUFFER_SIZE) {
                BYTE *tmp;

                tmp = heap_realloc(This->buf, read+This->buf_size);
                if(!tmp)
                    return E_OUTOFMEMORY;
                This->buf = tmp;
            }

            memcpy(This->buf+This->buf_size, buf, read);
            This->buf_size += read;
        }while(This->buf_size < MIME_TEST_SIZE && hres == S_OK);

        if(This->buf_size < MIME_TEST_SIZE && hres != S_FALSE)
            return S_OK;

        bscf = BSCF_FIRSTDATANOTIFICATION;
        if(hres == S_FALSE)
            bscf |= BSCF_LASTDATANOTIFICATION|BSCF_DATAFULLYAVAILABLE;

        if(!This->reported_mime) {
            BSTR raw_uri;

            hres = IUri_GetRawUri(This->uri, &raw_uri);
            if(FAILED(hres))
                return hres;

            hres = FindMimeFromData(NULL, raw_uri, This->buf, min(This->buf_size, MIME_TEST_SIZE),
                    This->mime, 0, &mime, 0);
            SysFreeString(raw_uri);
            if(FAILED(hres))
                return hres;

            heap_free(This->mime);
            This->mime = heap_strdupW(mime);
            CoTaskMemFree(mime);
            This->reported_mime = TRUE;
            if(This->protocol_sink)
                IInternetProtocolSink_ReportProgress(This->protocol_sink, BINDSTATUS_MIMETYPEAVAILABLE, This->mime);
        }
    }

    if(!This->protocol_sink)
        return S_OK;

    return IInternetProtocolSink_ReportData(This->protocol_sink, bscf, progress, progress_max);
}