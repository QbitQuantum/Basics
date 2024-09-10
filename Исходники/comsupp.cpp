void WINAPI _com_issue_errorex(HRESULT hr, IUnknown *punk, REFIID riid)
{
    void *pv;
    IErrorInfo *perrinfo = NULL;

    if (SUCCEEDED(punk->QueryInterface(riid, &pv)))
    {
        ISupportErrorInfo *pserrinfo = static_cast<ISupportErrorInfo *>(pv);
        if (pserrinfo->InterfaceSupportsErrorInfo(riid) == S_OK)
            (void)GetErrorInfo(0, &perrinfo);
        pserrinfo->Release();
    }

    com_error_handler(hr, perrinfo);
}