HRESULT CDirectSoundAecCapture::EnumDevices()
{
    if (FAILED(DirectSoundEnumerateA(DSoundEnum, (LPVOID)this)))
    {
        return E_FAIL;
    }

    if (FAILED(DirectSoundCaptureEnumerateA(DSoundCapEnum, (LPVOID)this)))
    {
        return E_FAIL;
    }

    return S_OK;
}