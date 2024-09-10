HRESULT CDriveItemPropertyStore::_InitializePropertyStore(const PROPERTYKEY *rgKeys, UINT cKeys, GETPROPERTYSTOREFLAGS flags)
{
    Log::WriteOutput(LogType::Debug, L"CDriveItemPropertyStore::_InitializePropertyStore(const PROPERTYKEY *rgKeys, UINT cKeys, GETPROPERTYSTOREFLAGS flags)");

    HRESULT hr = PSCreateMemoryPropertyStore(IID_PPV_ARGS(&_sppropstore));

    if (!SUCCEEDED(hr))
    {
        Log::WriteOutput(LogType::Error, L"PSCreateMemoryPropertyStore returned hr=%d", hr);
    }
    else
    {
        _flags = flags;

        CComPtr<IDriveItemPropertyHandler> sprph;

        hr = _gDriveShlExt->QueryInterface(IID_PPV_ARGS(&sprph));

        if (!SUCCEEDED(hr))
        {
            Log::WriteOutput(LogType::Error, L"CComPtr<IDriveItemPropertyHandler>->QueryInterface returned hr=%d", hr);
        }
        else
        {
            for (UINT i = 0; i < cKeys; i++)
            {
                if (flags & GPS_DELAYCREATION)
                {
                    _rgDelayedKeys.Add(rgKeys[i]);
                }
                else
                {
                    CPropVariant spropvar;

                    hr = sprph->GetProperty(_cpidl, rgKeys[i], &spropvar);

                    if (FAILED(hr))
                    {
                        // Intentional stomping of the previous HRESULT
                        // VT_EMPTY means that the value is not available for this item, so clear the
                        // propvariant and insert an empty instead
                        hr = spropvar.Reset();

                        if (!SUCCEEDED(hr))
                        {
                            Log::WriteOutput(LogType::Error, L"spropvar.Clear returned hr=%d", hr);

                            break;
                        }
                    }

                    if (SUCCEEDED(hr))
                    {
                        // It's ok for the property to not be there, the PROPVARIANT will be VT_EMPTY
                        hr = _sppropstore->SetValue(rgKeys[i], spropvar);

                        if (!SUCCEEDED(hr))
                        {
                            Log::WriteOutput(LogType::Error, L"_sppropstore->SetValue returned hr=%d", hr);

                            break;
                        }
                    }
                }
            }
        }
    }

    return hr;
}