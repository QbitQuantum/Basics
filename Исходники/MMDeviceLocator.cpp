HRESULT MMDeviceLocator::RegisterForWASAPI(){
    HRESULT hr = S_OK;
    IActivateAudioInterfaceAsyncOperation *asyncOp;

    Platform::String^ id = MediaDevice::GetDefaultAudioRenderId(Windows::Media::Devices::AudioDeviceRole::Default);
    hr = ActivateAudioInterfaceAsync(id->Data(), __uuidof(IAudioClient2), nullptr, this, &asyncOp);

    SafeRelease(&asyncOp);

    return hr;
}