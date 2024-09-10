static HRESULT vboxNetFltWinNotifyCheckNetAdp(IN INetCfgComponent *pComponent, OUT bool * pbShouldBind)
{
    HRESULT hr;
    LPWSTR pDevId;
    hr = pComponent->GetId(&pDevId);
    if (hr == S_OK)
    {
        if (!_wcsnicmp(pDevId, L"sun_VBoxNetAdp", sizeof(L"sun_VBoxNetAdp")/2))
        {
            *pbShouldBind = false;
        }
        else
        {
            hr = S_FALSE;
        }
        CoTaskMemFree(pDevId);
    }
    else
    {
        NonStandardAssertBreakpoint();
    }

    return hr;
}