static HRESULT init_bindctx(IBindCtx *bindctx, DWORD options,
       IBindStatusCallback *callback, IEnumFORMATETC *format)
{
    BIND_OPTS bindopts;
    HRESULT hres;

    if(options)
        FIXME("not supported options %08x\n", options);
    if(format)
        FIXME("format is not supported\n");

    bindopts.cbStruct = sizeof(BIND_OPTS);
    bindopts.grfFlags = BIND_MAYBOTHERUSER;
    bindopts.grfMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
    bindopts.dwTickCountDeadline = 0;

    hres = IBindCtx_SetBindOptions(bindctx, &bindopts);
    if(FAILED(hres))
       return hres;

    if(callback) {
        hres = RegisterBindStatusCallback(bindctx, callback, NULL, 0);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}