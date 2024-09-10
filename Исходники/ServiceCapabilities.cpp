//</SnippetListSupportedFormats1>
//<SnippetListSupportedEvents1>
// List all supported events on the service
void ListSupportedEvents(
    _In_ IPortableDeviceService* service)
{
    ComPtr<IPortableDeviceServiceCapabilities>     capabilities;
    ComPtr<IPortableDevicePropVariantCollection>   events;
    DWORD   numEvents = 0;

    // Get an IPortableDeviceServiceCapabilities interface from the IPortableDeviceService interface to
    // access the service capabilities-specific methods.
    HRESULT hr = service->Capabilities(&capabilities);
    if (FAILED(hr))
    {
        wprintf(L"! Failed to get IPortableDeviceServiceCapabilities from IPortableDeviceService, hr = 0x%lx\n", hr);
    }

    // Get all events supported by the service.
    if (SUCCEEDED(hr))
    {
        hr = capabilities->GetSupportedEvents(&events);
        if (FAILED(hr))
        {
            wprintf(L"! Failed to get supported events from the service, hr = 0x%lx\n", hr);
        }
    }

    // Get the number of supported events found on the service.
    if (SUCCEEDED(hr))
    {
        hr = events->GetCount(&numEvents);
        if (FAILED(hr))
        {
            wprintf(L"! Failed to get number of supported events, hr = 0x%lx\n", hr);
        }
    }

    // Loop through each event and display it
    if (SUCCEEDED(hr))
    {
        wprintf(L"\n%u Supported Events Found on the service\n\n", numEvents);

        for (DWORD index = 0; index < numEvents; index++)
        {
            PROPVARIANT event = {0};
            hr = events->GetAt(index, &event);

            if (SUCCEEDED(hr))
            {
                // We have an event.  It is assumed that
                // events are returned as VT_CLSID VarTypes.
                if (event.vt    == VT_CLSID && 
                    event.puuid != nullptr)
                {
                    DisplayEvent(capabilities.Get(), *event.puuid);
                    wprintf(L"\n");
                }
            }

            PropVariantClear(&event);
        }
    }
}