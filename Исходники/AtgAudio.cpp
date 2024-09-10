HRESULT WaveFile::GetPacketCumulativeBytes(DWORD* pdwData)
{
    assert( m_DpdsChunk.IsValid() );
    assert( pdwData != NULL );

    HRESULT hr = S_OK;

    if (!m_DpdsChunk.IsValid())
        return E_HANDLE;

    DWORD dwPacketCount;
    DWORD dwBufferSize;

    hr = GetPacketCumulativeBytesSize(&dwPacketCount, &dwBufferSize);
    if( FAILED( hr ) )
        return hr;

    hr = m_DpdsChunk.ReadData( 0, pdwData, dwBufferSize, NULL );
    if( FAILED( hr ) )
        return hr;

    // Endianness conversion
    #if defined(_XBOX)
        for (DWORD dw=0; dw<dwPacketCount; dw++) {
            pdwData[dw] = _byteswap_ulong(pdwData[dw]);
        }
    #endif

    return S_OK;
}