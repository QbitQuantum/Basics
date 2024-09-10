HRESULT zero_cowait(HANDLE hndl)
{
    DWORD wr;
    HRESULT hr = CoWaitForMultipleHandles(COWAIT_WAITALL, 0, 1, &hndl, &wr);
    if (SUCCEEDED(hr) && WAIT_OBJECT_0 == wr)
    {
        hr = S_OK;
    }
    else
    {
        hr = E_FAIL;
    }
    return hr;
}