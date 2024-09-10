    //--------------------------------------------------------------------------------------
    // Name: FilterAdaptiveDoubleExponential::UpdateSmoothingParameters()
    // Desc: Updates the smoothing parameters based on the smoothing filter's trend
    //--------------------------------------------------------------------------------------
    VOID FilterAdaptiveDoubleExponential::Update( const NUI_SKELETON_DATA* pSkeletonData, const FLOAT fDeltaTime  )
    {
        for (UINT i = 0; i < NUI_SKELETON_POSITION_COUNT; i++)
        {
            XMVECTOR vPreviousPosition  = m_DoubleExponentialFilter.m_History[ i ].m_vRawPosition;
            XMVECTOR vCurrentPosition   = pSkeletonData->SkeletonPositions[ i ];
            XMVECTOR vVelocity          = ( vCurrentPosition - vPreviousPosition ) / fDeltaTime;
            FLOAT fVelocity             = fabsf( XMVectorGetX( XMVector3Length( vVelocity ) ) );

            UpdateSmoothingParameters( i, fVelocity, pSkeletonData->eSkeletonPositionTrackingState[i] );

            m_DoubleExponentialFilter.Update( pSkeletonData, i, m_SmoothingParams[ i ] );
        }

        // Copy filtered data to output data
        XMemCpy( m_FilteredJoints, m_DoubleExponentialFilter.GetFilteredJoints(), sizeof( m_FilteredJoints ) );

    }