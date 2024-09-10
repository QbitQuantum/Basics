UINT PASCAL _Cover_waveInOpen( HWAVEIN *lphWaveIn,
                                UINT uDeviceID,
                                const WAVEFORMAT *lpFormat,
                                DWORD dwCallback,
                                DWORD dwInstance,
                                DWORD dwFlags )
{
    if( (dwFlags & CALLBACK_TYPEMASK) == CALLBACK_FUNCTION ) {
        CallBackFunc = dwCallback;
        dwCallback = GetWaveInCallBack( __WaveInCallBack );
    }
    return( waveInOpen( lphWaveIn, uDeviceID, lpFormat,
                         dwCallback, dwInstance, dwFlags ) );
}