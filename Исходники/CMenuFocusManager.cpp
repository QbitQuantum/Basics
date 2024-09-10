HRESULT CMenuFocusManager::IsTrackedWindowOrParent(HWND hWnd)
{
    for (int i = m_bandCount; --i >= 0;)
    {
        StackEntry& entry = m_bandStack[i];

        if (entry.type != TrackedMenuEntry)
        {
            HRESULT hr = entry.mb->IsWindowOwner(hWnd);
            if (FAILED_UNEXPECTEDLY(hr))
                return hr;
            if (hr == S_OK)
                return S_OK;
            if (entry.mb->_IsPopup() == S_OK)
            {
                CComPtr<IUnknown> site;
                CComPtr<IOleWindow> pw;
                hr = entry.mb->GetSite(IID_PPV_ARG(IUnknown, &site));
                if (FAILED_UNEXPECTEDLY(hr))
                    continue;
                hr = IUnknown_QueryService(site, SID_SMenuBandParent, IID_PPV_ARG(IOleWindow, &pw));
                if (FAILED_UNEXPECTEDLY(hr))
                    continue;

                HWND hParent;
                if (pw->GetWindow(&hParent) == S_OK && hParent == hWnd)
                    return S_OK;
            }
        }
    }

    return S_FALSE;
}