STDMETHODIMP SoundDA::SetChannelProperty(long User, NESTABLEPROP *pChan, VARIANT *newValue)
{
    int chan=pChan->Index;   

    if (chan>2) return E_EXCEEDS_MAX_CHANNELS;
   
    long numChans;
    
    HRESULT hRes = _EngineChannelList->GetNumberOfChannels(&numChans);
    if (FAILED(hRes)) return hRes;
        

        if (User==HwChan) 
        {
            variant_t val = (variant_t*)newValue;
            if (V_VT(newValue)==VT_R8 && (double)val!=chan)
                return E_INVALID_CHANNEL;
        }
        // Winsound supports only an input range of [-1 1]
        else if (User==OUTPUTRANGE)
        {
            if (V_ISARRAY (newValue) || V_ISVECTOR (newValue))
            {                            
                SAFEARRAY *ps = newValue->parray;
                if (ps==NULL)
                    return E_OUTOFMEMORY;
                                
                double *pr;
                
                HRESULT hr = SafeArrayAccessData (ps, (void **) &pr);
                if (FAILED (hr)) 
                {
                    SafeArrayDestroy (ps);
                    return hr;
                }
                
                if (pr[0]!=-1 || pr[1]!=1)
                {
                    SafeArrayUnaccessData (ps);
                    return E_INV_OUTPUT_RANGE;
                }
                
                SafeArrayUnaccessData (ps);
            }

        }


    if (numChans!=_nChannels)
        _nChannels = numChans;       
    
    return S_OK;
}