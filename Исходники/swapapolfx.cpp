HRESULT CSwapAPOLFX::Initialize(UINT32 cbDataSize, BYTE* pbyData)
{
    HRESULT                         hr = S_OK;
    PROPVARIANT                     var;

    IF_TRUE_ACTION_JUMP( ((NULL == pbyData) && (0 != cbDataSize)), hr = E_INVALIDARG, Exit);
    IF_TRUE_ACTION_JUMP( ((NULL != pbyData) && (0 == cbDataSize)), hr = E_POINTER, Exit);
    IF_TRUE_ACTION_JUMP( (cbDataSize != sizeof(APOInitSystemEffects) ), hr = E_INVALIDARG, Exit);

    APOInitSystemEffects* papoSysFxInit = (APOInitSystemEffects*)pbyData;

    //
    //  Store locally for later reference
    //
    m_spAPOSystemEffectsProperties = papoSysFxInit->pAPOSystemEffectsProperties;

    //
    //  Get the current value
    //
    PropVariantInit(&var);

    if (m_spAPOSystemEffectsProperties != NULL)
    {
        // Get the state of whether channel swap LFX is enabled or not
        hr = m_spAPOSystemEffectsProperties->GetValue(PKEY_Endpoint_Enable_Channel_Swap_LFX, &var);

        if (SUCCEEDED(hr) && (var.vt == VT_UI4))
        {
            if (var.ulVal == 0L)
            {
                m_fEnableSwapLFX = FALSE;
            }
            else
            {
                m_fEnableSwapLFX = TRUE;
            }
        }
        else
        {
            PropVariantClear(&var);
        }
    }

    //
    //  Register for notification of registry updates
    //
    hr = m_spEnumerator.CoCreateInstance(__uuidof(MMDeviceEnumerator));
    IF_FAILED_JUMP(hr, Exit);

    hr = m_spEnumerator->RegisterEndpointNotificationCallback(this);
    IF_FAILED_JUMP(hr, Exit);

     m_bIsInitialized = true;


Exit:
    return hr;
}