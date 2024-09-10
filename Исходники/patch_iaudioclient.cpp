HRESULT __stdcall initialize_patch(
    IAudioClient* this_, AUDCLNT_SHAREMODE ShareMode, DWORD StreamFlags, 
    REFERENCE_TIME hnsBufferDuration, REFERENCE_TIME hnsPeriodicity, 
    const WAVEFORMATEX* pFormat, LPCGUID AudioSessionGuid)
{
    // synchronize initializing so it doesn't happen while streams are being flushed
    HANDLE audio_router_mutex = OpenMutexW(SYNCHRONIZE, FALSE, L"Local\\audio-router-mutex");
    assert(audio_router_mutex != NULL);
    if(audio_router_mutex)
    {
        DWORD res = WaitForSingleObject(audio_router_mutex, INFINITE);
        assert(res == WAIT_OBJECT_0);
    }

    IAudioClient* proxy = get_duplicate(this_)->proxy;
    LPCGUID guid = ((GUID***)this_)[0][17];
    DWORD_PTR* old_vftptr = swap_vtable(this_);
    HRESULT hr = proxy->Initialize(
        ShareMode, 
        StreamFlags | 
        AUDCLNT_SESSIONFLAGS_EXPIREWHENUNOWNED | 
        AUDCLNT_SESSIONFLAGS_DISPLAY_HIDEWHENEXPIRED,
        hnsBufferDuration, 
        hnsPeriodicity, 
        pFormat, 
        guid);
    ((DWORD_PTR**)this_)[0] = old_vftptr;
    if(hr != S_OK)
        tell_error(hr);
    else
        *((WORD***)this_)[0][18] = pFormat->nBlockAlign;
    if(hr == S_OK)
    {
        for(iaudioclient_duplicate* next = get_duplicate(this_)->next;
            next != NULL; next = next->next)
        {
            HRESULT hr2 = next->proxy->Initialize(
                ShareMode,
                StreamFlags |
                AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM |
                AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY |
                AUDCLNT_SESSIONFLAGS_EXPIREWHENUNOWNED |
                AUDCLNT_SESSIONFLAGS_DISPLAY_HIDEWHENEXPIRED,
                hnsBufferDuration,
                hnsPeriodicity,
                pFormat,
                guid);
            if(hr2 != S_OK)
                tell_error(hr2);
        }
    }

    ReleaseMutex(audio_router_mutex);
    CloseHandle(audio_router_mutex);
    return hr;
}