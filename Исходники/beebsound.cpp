void DirectSoundStreamer::Stream( void const *pSamples )
{
    // Verify buffer availability
    DWORD play, write;
    if( FAILED( m_pDirectSoundBuffer->GetCurrentPosition( &play, &write ) ) )
        return;
    if( write < play )
        write += DWORD( m_physical );
    std::size_t begin( m_begin );
    if( begin < play )
        begin += m_physical;
    if( begin < write )
        begin = std::size_t( write );
    std::size_t end( begin + m_stream );
    if( play + m_virtual < end )
        return;
    begin %= m_physical;

    // Copy samples to buffer
    void *ps[ 2 ];
    DWORD sizes[ 2 ];
    HRESULT hResult( m_pDirectSoundBuffer->Lock( DWORD( begin ), DWORD( m_stream ), &ps[ 0 ], &sizes[ 0 ], &ps[ 1 ], &sizes[ 1 ], 0 ) );
    if( FAILED( hResult ) )
    {
        if( hResult != DSERR_BUFFERLOST )
            return;
        m_pDirectSoundBuffer->Restore();
        if( FAILED( m_pDirectSoundBuffer->Lock( DWORD( begin ), DWORD( m_stream ), &ps[ 0 ], &sizes[ 0 ], &ps[ 1 ], &sizes[ 1 ], 0 ) ) )
            return;
    }
    using std::memcpy;
    memcpy( ps[ 0 ], pSamples, std::size_t( sizes[ 0 ] ) );
    if( ps[ 1 ] )
        memcpy( ps[ 1 ], static_cast< char const * >( pSamples ) + sizes[ 0 ], std::size_t( sizes[ 1 ] ) );
    m_pDirectSoundBuffer->Unlock( ps[ 0 ], sizes[ 0 ], ps[ 1 ], sizes[ 1 ] );

    // Select next buffer
    m_begin = end % m_physical;
}