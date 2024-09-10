STDMETHODIMP CVMR7AllocatorPresenter::CreateRenderer(IUnknown** ppRenderer)
{
    CheckPointer(ppRenderer, E_POINTER);

    *ppRenderer = nullptr;
    CComPtr<IBaseFilter> pBF;

    if (FAILED(pBF.CoCreateInstance(CLSID_VideoMixingRenderer))) {
        return E_FAIL;
    }

    CComQIPtr<IVMRFilterConfig> pConfig = pBF;
    if (!pConfig) {
        return E_FAIL;
    }

    if (FAILED(pConfig->SetRenderingMode(VMRMode_Renderless))) {
        return E_FAIL;
    }

    CComQIPtr<IVMRSurfaceAllocatorNotify> pSAN = pBF;
    if (!pSAN) {
        return E_FAIL;
    }

    if (FAILED(pSAN->AdviseSurfaceAllocator(MY_USER_ID, static_cast<IVMRSurfaceAllocator*>(this)))
            || FAILED(AdviseNotify(pSAN))) {
        return E_FAIL;
    }

    CComPtr<IPin> pPin = GetFirstPin(pBF);
    CComQIPtr<IMemInputPin> pMemInputPin = pPin;
    m_fUseInternalTimer = HookNewSegmentAndReceive((IPinC*)(IPin*)pPin, (IMemInputPinC*)(IMemInputPin*)pMemInputPin);

    *ppRenderer = (IUnknown*)pBF.Detach();

    return S_OK;
}