static HRESULT extract_cab_file(install_ctx_t *ctx)
{
    size_t path_len, file_len;
    WCHAR *ptr;
    HRESULT hres;

    hres = ExtractFilesW(ctx->cache_file, ctx->tmp_dir, 0, NULL, NULL, 0);
    if(FAILED(hres)) {
        WARN("ExtractFilesW failed: %08x\n", hres);
        return hres;
    }

    path_len = strlenW(ctx->tmp_dir);
    file_len = strlenW(ctx->file_name);
    ctx->install_file = heap_alloc((path_len+file_len+2)*sizeof(WCHAR));
    if(!ctx->install_file)
        return E_OUTOFMEMORY;

    memcpy(ctx->install_file, ctx->tmp_dir, path_len*sizeof(WCHAR));
    ctx->install_file[path_len] = '\\';
    memcpy(ctx->install_file+path_len+1, ctx->file_name, (file_len+1)*sizeof(WCHAR));

    /* NOTE: Assume that file_name contains ".cab" extension */
    ptr = ctx->install_file+path_len+1+file_len-3;

    memcpy(ptr, infW, sizeof(infW));
    if(file_exists(ctx->install_file)) {
        ctx->install_type = INSTALL_INF;
        return S_OK;
    }

    memcpy(ptr, dllW, sizeof(dllW));
    if(file_exists(ctx->install_file)) {
        ctx->install_type = INSTALL_DLL;
        return S_OK;
    }

    memcpy(ptr, ocxW, sizeof(ocxW));
    if(file_exists(ctx->install_file)) {
        ctx->install_type = INSTALL_DLL;
        return S_OK;
    }

    FIXME("No known install file\n");
    return E_NOTIMPL;
}