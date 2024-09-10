    //--------------------------------------------------------------------------------------
    // Name: Update()
    // Desc: Adds a new frame of positions, updates the coordiante system, and calculates 
    //       left and right hand.
    //--------------------------------------------------------------------------------------
    VOID SpineRelativeCameraSpaceCoordinateSystem::Update( const NUI_SKELETON_FRAME* pRawSkeletonFrame, INT iSkeletonIndex, XMVECTOR vLeft, XMVECTOR vRight )
    {
        if ( pRawSkeletonFrame == NULL ) return;
        if ( iSkeletonIndex < 0 || iSkeletonIndex >= NUI_SKELETON_COUNT ) return;
        CONST XMVECTOR *pSkeletonPosition = &pRawSkeletonFrame->SkeletonData[iSkeletonIndex].SkeletonPositions[0];

        if ( m_dwLastTrackingID != pRawSkeletonFrame->SkeletonData[iSkeletonIndex].dwTrackingID )
        {
            m_vAverageNormalToGravity = pRawSkeletonFrame->vNormalToGravity;
        }
        else
        {
            m_vAverageNormalToGravity = m_fSpineUpdateRate * m_vAverageNormalToGravity +
                 pRawSkeletonFrame->vNormalToGravity * ( 1.0f - m_fSpineUpdateRate );
        }
        
#if 0
        CHAR out[255];
        sprintf_s( out, "x=%f,y=%f,z=%f,w=%f\n", pRawSkeletonFrame->vNormalToGravity.x, pRawSkeletonFrame->vNormalToGravity.y, pRawSkeletonFrame->vNormalToGravity.z, pRawSkeletonFrame->vNormalToGravity.w );
        OutputDebugString( out );
#endif 
        m_matRotateToNormalToGravity = NuiTransformMatrixLevel( m_vAverageNormalToGravity );
        XMVECTOR vSpineTilted = XMVector3Transform( pSkeletonPosition[NUI_SKELETON_POSITION_SPINE], m_matRotateToNormalToGravity );
        XMVECTOR vHeadTilted = XMVector3Transform( pSkeletonPosition[NUI_SKELETON_POSITION_HEAD], m_matRotateToNormalToGravity );
        m_vLeftHandRelative = XMVector3Transform( vLeft, m_matRotateToNormalToGravity );
        m_vRightHandRelative = XMVector3Transform( vRight, m_matRotateToNormalToGravity );


        FLOAT fSpineHeadLength = XMVectorGetY( vHeadTilted ) - XMVectorGetY( vSpineTilted );
        if ( m_dwLastTrackingID != pRawSkeletonFrame->SkeletonData[iSkeletonIndex].dwTrackingID )
        {
            m_dwLastTrackingID = pRawSkeletonFrame->SkeletonData[iSkeletonIndex].dwTrackingID;
            m_vAverageSpine = vSpineTilted;
            m_fAverageSpineHeadLength = fSpineHeadLength;
        }
        else
        {
            m_vAverageSpine = m_vAverageSpine * m_fSpineUpdateRate + 
                vSpineTilted * ( 1.0f - m_fSpineUpdateRate );
            m_fAverageSpineHeadLength = ATG::Lerp( fSpineHeadLength, m_fAverageSpineHeadLength, m_fBodySizeUpdateRate );
        }

        m_vEstiamtedPivotOffsetLeft = XMVectorSet( m_fAverageSpineHeadLength * 0.3f, m_fAverageSpineHeadLength * 0.1f, 0.0f, 0.0f );
        m_vEstiamtedPivotOffsetRight = XMVectorSet( -m_fAverageSpineHeadLength * 0.3f, m_fAverageSpineHeadLength * 0.1f, 0.0f, 0.0f );
        m_vRightHandRelative -= m_vAverageSpine;
        m_vRightHandRelative += m_vEstiamtedPivotOffsetRight;
        m_vLeftHandRelative -= m_vAverageSpine;
        m_vLeftHandRelative += m_vEstiamtedPivotOffsetLeft;
        static XMVECTOR vFlipZ = XMVectorSet( 1.0f, 1.0f, -1.0f, 1.0f );
        m_vRightHandRelative *= vFlipZ;
        m_vLeftHandRelative *= vFlipZ;

    }