    bool Device::apiInit(const Desc& desc)
    {
        DeviceApiData* pData = new DeviceApiData;
        mpApiData = pData;

        if (desc.enableDebugLayer)
        {
            ID3D12DebugPtr pDebug;
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebug))))
            {
                pDebug->EnableDebugLayer();
            }
        }

        // Create the DXGI factory
        d3d_call(CreateDXGIFactory1(IID_PPV_ARGS(&mpApiData->pDxgiFactory)));

        mApiHandle = createDevice(mpApiData->pDxgiFactory, getD3DFeatureLevel(desc.apiMajorVersion, desc.apiMinorVersion), desc.createDeviceFunc, mRgb32FloatSupported);
        if (mApiHandle == nullptr)
        {
            return false;
        }

        for (uint32_t i = 0; i < kQueueTypeCount; i++)
        {
            for (uint32_t j = 0; j < desc.cmdQueues[i]; j++)
            {
                // Create the command queue
                D3D12_COMMAND_QUEUE_DESC cqDesc = {};
                cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
                cqDesc.Type = getApiCommandQueueType((LowLevelContextData::CommandQueueType)i);

                ID3D12CommandQueuePtr pQueue;
                if (FAILED(mApiHandle->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&pQueue))))
                {
                    logError("Failed to create command queue");
                    return nullptr;
                }

                mCmdQueues[i].push_back(pQueue);
            }
        }

        uint64_t freq;
        d3d_call(getCommandQueueHandle(LowLevelContextData::CommandQueueType::Direct, 0)->GetTimestampFrequency(&freq));
        mGpuTimestampFrequency = 1000.0 / (double)freq;

        return true;
    }