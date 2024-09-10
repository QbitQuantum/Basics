DWORD WINAPI OnSecurityCenterHealthChange(LPVOID lpParameter)
{
    HRESULT hr = S_OK;
    WSC_SECURITY_PROVIDER_HEALTH health = WSC_SECURITY_PROVIDER_HEALTH_GOOD;

    if (SUCCEEDED(hr))
    {
        hr = WscGetSecurityProviderHealth(WSC_SECURITY_PROVIDER_INTERNET_SETTINGS, &health);
        if (SUCCEEDED(hr))
        {
            wprintf(L"Internet Settings are %s, The Security Center service is %s\n", 
                    (WSC_SECURITY_PROVIDER_HEALTH_GOOD == health)?L"OK":L"Not OK",
                    (S_FALSE == hr)?L"Not Running":L"Running");
        }
    }
    if (SUCCEEDED(hr))
    {
        hr = WscGetSecurityProviderHealth(WSC_SECURITY_PROVIDER_ALL, &health);
        if (SUCCEEDED(hr))
        {
            wprintf(L"Security Center says the machines security health is %s, The Security Center service is %s\n", 
                    (WSC_SECURITY_PROVIDER_HEALTH_GOOD == health)?L"OK":L"Not OK",
                    (S_FALSE == hr)?L"Not Running":L"Running");
        }
    }
    if (FAILED(hr))
    {
        wprintf(L"Failed to get health status from Security Center: Error: 0x%X\n", hr);
    }
    return 0;
}