// ----------------------------------------------------------------------------
//
AudioVolumeController* AudioVolumeController::createVolumeController( )
{
    HRESULT hr;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDefaultDevice = NULL;
    IAudioEndpointVolume *endpointVolume = NULL;
    LPWSTR pstrDefaultId = NULL;
    IPropertyStore *pProperties = NULL;

    try {
        hr = CoCreateInstance(
               CLSID_MMDeviceEnumerator, NULL,
               CLSCTX_ALL, IID_IMMDeviceEnumerator,
               (void**)&pEnumerator);
        AUDIO_VOLUME_ASSERT( hr, "Cannot create COM device enumerator instance" );

        // Get the default audio endpoint (if we don't get one its not an error)
        hr = pEnumerator->GetDefaultAudioEndpoint( eRender, eConsole, &pDefaultDevice );
        AUDIO_VOLUME_ASSERT( hr, "Cannot get default audio render device" );

        hr = pDefaultDevice->OpenPropertyStore( STGM_READ, &pProperties );
        AUDIO_VOLUME_ASSERT( hr, "Cannot open IMMDevice property store" );

        PROPVARIANT varName;
        // Initialize container for property value.
        PropVariantInit(&varName);

        // Get the endpoint's friendly-name property.
        hr = pProperties->GetValue( PKEY_Device_DeviceDesc , &varName);
        AUDIO_VOLUME_ASSERT( hr, "Cannot open IMMDevice name property" );

        CString render_name = CW2A( varName.pwszVal );

        DMXStudio::log_status( "Default audio render device '%s'", render_name );

        PropVariantClear(&varName);

        hr = pDefaultDevice->Activate( IID_IAudioEndpointVolume, CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume );
        AUDIO_VOLUME_ASSERT( hr, "Cannot activate default render device" );

        SAFE_RELEASE( pDefaultDevice );
        SAFE_RELEASE( pProperties );
        SAFE_RELEASE( pEnumerator );

        CoTaskMemFree( pstrDefaultId );

        return new AudioVolumeController( endpointVolume, render_name );
    }
    catch ( ... ) {
        CoTaskMemFree( pstrDefaultId );

        SAFE_RELEASE( pDefaultDevice );
        SAFE_RELEASE( pProperties );
        SAFE_RELEASE( pEnumerator );

        throw;
    }
}