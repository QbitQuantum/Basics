HRESULT DSW_InitInputDevice( DSoundWrapper *dsw, LPGUID lpGUID )
{
    HRESULT hr = dswDSoundEntryPoints.DirectSoundCaptureCreate(  lpGUID, &dsw->dsw_pDirectSoundCapture,   NULL );
    if( hr != DS_OK ) return hr;
    return hr;
}