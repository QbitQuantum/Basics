    //---------------------------------------------------------------------
    void D3D11Device::TransferOwnership(ID3D11DeviceN* d3d11device)
    {
        assert(mD3D11Device.Get() != d3d11device);
        ReleaseAll();

        if (d3d11device)
        {
            HRESULT hr = S_OK;

            mD3D11Device.Attach(d3d11device);

            // get DXGI factory from device
            ComPtr<IDXGIDeviceN> pDXGIDevice;
            ComPtr<IDXGIAdapterN> pDXGIAdapter;
            if(SUCCEEDED(mD3D11Device.As(&pDXGIDevice))
            && SUCCEEDED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapterN), (void **)pDXGIAdapter.GetAddressOf())))
            {
                pDXGIAdapter->GetParent(__uuidof(IDXGIFactoryN), (void **)mDXGIFactory.ReleaseAndGetAddressOf());

                // We intentionally check for ID3D10Device support instead of ID3D11Device as CheckInterfaceSupport() is not supported for later.
                // We hope, that there would be one UMD for both D3D10 and D3D11, or two different but with the same version number,
                // or with different but correlated version numbers, so that blacklisting could be done with high confidence level.
                if(FAILED(pDXGIAdapter->CheckInterfaceSupport(IID_ID3D10Device /* intentionally D3D10, not D3D11 */, &mDriverVersion)))
                    mDriverVersion.QuadPart = 0;
            }

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            mD3D11Device->GetImmediateContext(mImmediateContext.ReleaseAndGetAddressOf());
#elif OGRE_PLATFORM == OGRE_PLATFORM_WINRT
            mD3D11Device->GetImmediateContext1(mImmediateContext.ReleaseAndGetAddressOf());
#endif

#if OGRE_D3D11_PROFILING
            hr = mImmediateContext.As(&mPerf);
            if(FAILED(hr) || !mPerf->GetStatus())
                mPerf.Reset();
#endif

            hr = mD3D11Device.As(&mInfoQueue);
            if (SUCCEEDED(hr))
            {
                mInfoQueue->ClearStoredMessages();
                mInfoQueue->ClearRetrievalFilter();
                mInfoQueue->ClearStorageFilter();

                D3D11_INFO_QUEUE_FILTER filter;
                ZeroMemory(&filter, sizeof(D3D11_INFO_QUEUE_FILTER));
                vector<D3D11_MESSAGE_SEVERITY>::type severityList;

                switch(mExceptionsErrorLevel)
                {
                case D3D_NO_EXCEPTION:
                    severityList.push_back(D3D11_MESSAGE_SEVERITY_CORRUPTION);
                case D3D_CORRUPTION:
                    severityList.push_back(D3D11_MESSAGE_SEVERITY_ERROR);
                case D3D_ERROR:
                    severityList.push_back(D3D11_MESSAGE_SEVERITY_WARNING);
                case D3D_WARNING:
                case D3D_INFO:
                    severityList.push_back(D3D11_MESSAGE_SEVERITY_INFO);
                default: 
                    break;
                }


                if (severityList.size() > 0)
                {
                    filter.DenyList.NumSeverities = severityList.size();
                    filter.DenyList.pSeverityList = &severityList[0];
                }

                mInfoQueue->AddStorageFilterEntries(&filter);
                mInfoQueue->AddRetrievalFilterEntries(&filter);
            }

            // If feature level is 11, create class linkage
            if (mD3D11Device->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_0)
            {
                hr = mD3D11Device->CreateClassLinkage(mClassLinkage.ReleaseAndGetAddressOf());
            }
        }
    }