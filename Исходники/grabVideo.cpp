void KinectGrabber::Kinect_UnInit( )
{
    // Shut down Nui and clean up data stream objects
    NuiShutdown( );

    if( m_hNextVideoFrameEvent && ( m_hNextVideoFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextVideoFrameEvent );
        m_hNextVideoFrameEvent = NULL;
    }
    if( m_hNextDepthFrameEvent && ( m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextDepthFrameEvent );
        m_hNextDepthFrameEvent = NULL;
    }
    if( m_hNextSkeletonFrameEvent && ( m_hNextSkeletonFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextSkeletonFrameEvent );
        m_hNextSkeletonFrameEvent = NULL;
    }
	if( m_hNextDepthPlayerFrameEvent && ( m_hNextDepthPlayerFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextDepthPlayerFrameEvent );
        m_hNextDepthPlayerFrameEvent = NULL;
    }


	// Shutdown of audio stuff
	SAFE_RELEASE(pDMO);
    SAFE_RELEASE(pPS);

    AvRevertMmThreadCharacteristics(mmHandle);
    CoUninitialize();
}