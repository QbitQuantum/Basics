HRESULT protocol_continue(Protocol *protocol, PROTOCOLDATA *data)
{
    HRESULT hres;

    if (!data) {
        WARN("Expected pProtocolData to be non-NULL\n");
        return S_OK;
    }

    if(!protocol->request) {
        WARN("Expected request to be non-NULL\n");
        return S_OK;
    }

    if(!protocol->protocol_sink) {
        WARN("Expected IInternetProtocolSink pointer to be non-NULL\n");
        return S_OK;
    }

    if(protocol->flags & FLAG_ERROR) {
        protocol->flags &= ~FLAG_ERROR;
        protocol->vtbl->on_error(protocol, (DWORD)data->pData);
        return S_OK;
    }

    if(protocol->post_stream)
        return write_post_stream(protocol);

    if(data->pData == (LPVOID)BINDSTATUS_DOWNLOADINGDATA) {
        hres = protocol->vtbl->start_downloading(protocol);
        if(FAILED(hres)) {
            protocol_close_connection(protocol);
            report_result(protocol, hres);
            return S_OK;
        }

        if(protocol->bindf & BINDF_NEEDFILE) {
            WCHAR cache_file[MAX_PATH];
            DWORD buflen = sizeof(cache_file);

            if(InternetQueryOptionW(protocol->request, INTERNET_OPTION_DATAFILE_NAME,
                    cache_file, &buflen)) {
                report_progress(protocol, BINDSTATUS_CACHEFILENAMEAVAILABLE, cache_file);
            }else {
                FIXME("Could not get cache file\n");
            }
        }

        protocol->flags |= FLAG_FIRST_CONTINUE_COMPLETE;
    }

    if(data->pData >= (LPVOID)BINDSTATUS_DOWNLOADINGDATA) {
        BOOL res;

        /* InternetQueryDataAvailable may immediately fork and perform its asynchronous
         * read, so clear the flag _before_ calling so it does not incorrectly get cleared
         * after the status callback is called */
        protocol->flags &= ~FLAG_REQUEST_COMPLETE;
        res = InternetQueryDataAvailable(protocol->request, &protocol->available_bytes, 0, 0);
        if(res) {
            protocol->flags |= FLAG_REQUEST_COMPLETE;
            report_data(protocol);
        }else if(GetLastError() != ERROR_IO_PENDING) {
            protocol->flags |= FLAG_REQUEST_COMPLETE;
            WARN("InternetQueryDataAvailable failed: %d\n", GetLastError());
            report_result(protocol, INET_E_DATA_NOT_AVAILABLE);
        }
    }

    return S_OK;
}