static int  Create (vlc_object_t *p_this)
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys;
    HRESULT hr;

    p_filter->p_sys = p_sys = (filter_sys_t*) malloc(sizeof(filter_sys_t));
    if (!p_sys)
        return VLC_ENOMEM;

    if (TryEnterMTA(p_this))
        goto error;

    p_sys->cpVoice = nullptr;
    hr = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**) &p_sys->cpVoice);
    if (SUCCEEDED(hr)) {
        ISpObjectToken*        cpVoiceToken = nullptr;
        IEnumSpObjectTokens*   cpEnum = nullptr;
        ULONG ulCount = 0;

        hr = SpEnumTokens(SPCAT_VOICES, nullptr, nullptr, &cpEnum);
        if (SUCCEEDED(hr)) {
            // Get the number of voices.
            hr = cpEnum->GetCount(&ulCount);
            if (SUCCEEDED (hr))
            {
                int voiceIndex = var_InheritInteger(p_this, "sapi-voice");
                if (voiceIndex > - 1)
                {
                    if (voiceIndex < ulCount) {
                        hr = cpEnum->Item(voiceIndex, &cpVoiceToken);
                        if (SUCCEEDED(hr)) {
                            hr = p_sys->cpVoice->SetVoice(cpVoiceToken);
                            if (SUCCEEDED(hr)) {
                                msg_Dbg(p_this, "Selected voice %d", voiceIndex);
                            }
                            else {
                                msg_Err(p_this, "Failed to set voice %d", voiceIndex);
                            }
                            cpVoiceToken->Release();
                            cpVoiceToken = nullptr;
                        }
                    }
                    else
                        msg_Err(p_this, "Voice index exceeds available count");
                }
            }
            cpEnum->Release();
            cpEnum = nullptr;
        }

        if (SUCCEEDED(hr)) {
            hr = p_sys->cpVoice->SetOutput(nullptr, TRUE);
        }
    }
    else
    {
        msg_Err(p_filter, "Could not create SpVoice");
    }

    LeaveMTA();

    p_filter->pf_render_text = RenderText;

    return VLC_SUCCESS;

error:
    free(p_sys);
    return VLC_EGENERIC;
}