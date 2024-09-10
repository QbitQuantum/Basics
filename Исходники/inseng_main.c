static HRESULT download_url(InstallEngine *This, char *id, char *display, char *url, DWORD flags, DWORD dl_size)
{
    struct downloadcb *callback = NULL;
    char *filename    = NULL;
    IUnknown *unk     = NULL;
    IMoniker *mon     = NULL;
    IBindCtx *bindctx = NULL;
    HANDLE event      = NULL;
    HRESULT hr;

    if (!This->downloaddir)
    {
        WARN("No download directory set\n");
        return E_FAIL;
    }

    hr = generate_moniker(This->baseurl, url, flags, &mon);
    if (FAILED(hr))
    {
        FIXME("Failed to create moniker\n");
        return hr;
    }

    event = CreateEventW(NULL, TRUE, FALSE, NULL);
    if (!event)
    {
        IMoniker_Release(mon);
        return E_FAIL;
    }

    filename = strrchr(url, '/');
    if (!filename) filename = url;

    filename = merge_path(This->downloaddir, filename);
    if (!filename)
    {
        hr = E_OUTOFMEMORY;
        goto error;
    }

    hr = downloadcb_create(This, event, filename, id, display, dl_size, &callback);
    if (FAILED(hr)) goto error;

    hr = CreateAsyncBindCtx(0, &callback->IBindStatusCallback_iface, NULL, &bindctx);
    if(FAILED(hr)) goto error;

    hr = IMoniker_BindToStorage(mon, bindctx, NULL, &IID_IUnknown, (void**)&unk);
    if (FAILED(hr)) goto error;
    if (unk) IUnknown_Release(unk);

    heap_free(filename);
    IMoniker_Release(mon);
    IBindCtx_Release(bindctx);

    WaitForSingleObject(event, INFINITE);
    hr = callback->hr;

    CloseHandle(event);
    IBindStatusCallback_Release(&callback->IBindStatusCallback_iface);
    return hr;

error:
    if (mon) IMoniker_Release(mon);
    if (event) CloseHandle(event);
    if (callback) IBindStatusCallback_Release(&callback->IBindStatusCallback_iface);
    if (bindctx) IBindCtx_Release(bindctx);
    if (filename) heap_free(filename);
    return hr;
}