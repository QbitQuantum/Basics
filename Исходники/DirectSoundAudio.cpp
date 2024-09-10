    // ////////////////////////////////////////////////////////////////////
    //
    // ////////////////////////////////////////////////////////////////////
    bool DirectSound8Audio::VInitialize()
    {
        if(Audio::IsInitialized()) {
            return (true);
        }

        Audio::SetInitialized(false);
        Release(m_pDS);
        HRESULT hr;

        // Create IDirectSound using the primary sound device
        if(FAILED(hr = DirectSoundCreate8(NULL, &m_pDS, NULL))) {
            GF_LOG_TRACE_ERR("DirectSound8Audio::VInitialize()", "Failed to initialized the DirectSound interface");
            return (false);
        }

        if(FAILED(hr = m_pDS->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY))) {
            GF_LOG_TRACE_ERR("DirectSound8Audio::VInitialize()", "Failed to set the coop level of the DirectSound interface");
            return (false);
        }

        if(FAILED(hr = SetPrimaryBufferFormat(8, 44100, 16))) {
            GF_LOG_TRACE_ERR("DirectSound8Audio::VInitialize()", "Failed to set the primary buffer format of the DirectSound interface");
            return (false);
        }

        Audio::SetInitialized(true);
        m_AllSamples.clear();

        return (true);
    }