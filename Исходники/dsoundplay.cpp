/*!
 * @brief Sets up the DirectSound for playback
 * @details Example code:
 * @code
 * HRESULT hr;
 * struct dsound_data * p_retval = (struct dsound_data*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct dsound_data));
 * if (NULL != p_retval)
 * {
 *     hr = init_ds_data(hWnd, p_WFE, p_retval);
 *     if (SUCCEEDED(hr))
 *     {
            HeapFree(GetProcessHeap(), 0, p_tib);
 *         return (DSOUNDPLAY)(p_retval);
 *     }
 * }
 * debug_outputln("%s %4.4u", __FILE__, __LINE__);
 * HeapFree(GetProcessHeap(), 0, p_retval);
 * return NULL;
 * @endcode
 * @param[in] hwnd handle to the window that goes into the call of IDirectSound::SetCooperationLevel. Can be NULL, in which case either
 * a foreground window or the desktop window will be used. See <a href="http://msdn.microsoft.com/en-us/library/ms898135.aspx">this link</a> for more information.
 * @param[in] p_WFE pointer to the WAVEFORMATEX structure, describing the data to be played.
 * @param[out] p_ds_data refernce to the structure, whose members will be filled with DirectSound interface pointers.
 * @retrun returns the status of the operation, test it with SUCCEEDED() or FAILED() macros. 
 */
static HRESULT init_ds_data(HWND hwnd, WAVEFORMATEX const * p_WFE, dxaudio_player_thread_information_block_t * p_ds_data)
{
    HRESULT hr = E_FAIL;
    hr = DirectSoundCreate8(&DSDEVID_DefaultVoicePlayback, &p_ds_data->p_direct_sound_8_, NULL);
    if (FAILED(hr))
    {
        debug_outputln("%s %4.4u : %x", __FILE__, __LINE__, hr);
        goto error;
    }
    if (NULL == hwnd)
    {
        hwnd = GetForegroundWindow();
    }
    if (NULL == hwnd)
    {
        hwnd = GetDesktopWindow();
    }
    /* Quoting MSDN: */
    /* "[..]After creating a device object, you must set the cooperative level  */
    /* for the device by using the IDirectSound8::SetCooperativeLevel method.  */
    /* Unless you do this, no sounds will be heard." */
    hr = p_ds_data->p_direct_sound_8_->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
    if (FAILED(hr))
    {
        debug_outputln("%4.4u %s : 0x%8.8x", __LINE__, __FILE__, hr);
        goto error;
    }
    CopyMemory(&p_ds_data->p_dsound_data->wfe_, p_WFE, sizeof(WAVEFORMATEX));
    p_ds_data->p_dsound_data->wfe_.cbSize = sizeof(WAVEFORMATEX);
    p_ds_data->p_dsound_data->nSingleBufferSize_ = p_ds_data->p_dsound_data->play_settings_.play_buffer_size_;
    hr = create_buffers(p_ds_data->p_direct_sound_8_, 
        &p_ds_data->p_dsound_data->wfe_, 
        p_ds_data->p_dsound_data->number_of_chunks_,
        p_ds_data->p_dsound_data->nSingleBufferSize_,
        &p_ds_data->p_primary_sound_buffer_,
        &p_ds_data->p_secondary_sound_buffer_
    );
    if (FAILED(hr))
    {
        debug_outputln("%s %4.4u : %x", __FILE__, __LINE__, hr);
        goto error;
    }
    hr = set_play_notifications(p_ds_data->p_secondary_sound_buffer_, &p_ds_data->notification_array_[0], COUNTOF_ARRAY(p_ds_data->notification_array_));
    if (FAILED(hr))
    {
        debug_outputln("%s %4.4u : %x", __FILE__, __LINE__, hr);
        goto error;
    }
    return hr;
error:
    if (NULL != p_ds_data->p_direct_sound_8_)
    {
        p_ds_data->p_direct_sound_8_->Release();
        p_ds_data->p_direct_sound_8_ = NULL;
    }
    return hr;
}