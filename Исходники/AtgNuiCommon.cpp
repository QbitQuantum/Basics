    //--------------------------------------------------------------------------------------
    // Applies tilt correction to the skeleton data data. Source and destination can be the same
    //--------------------------------------------------------------------------------------
    VOID ApplyTiltCorrectionInPlayerSpace( NUI_SKELETON_FRAME* pDstSkeleton, const NUI_SKELETON_FRAME* pSrcSkeleton )
    {
        assert( pDstSkeleton );
        assert( pSrcSkeleton );

        if ( !pDstSkeleton ||
             !pSrcSkeleton )
        {
            return;
        }

        static const XMVECTOR vUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
        static XMVECTOR vAverageSpine[ NUI_SKELETON_COUNT ] = { XMVectorZero(), XMVectorZero(), XMVectorZero(),
                                                                XMVectorZero(), XMVectorZero(), XMVectorZero() };
        static XMVECTOR vAverageNormalToGravity = pSrcSkeleton->vNormalToGravity;

        // Get a valid up vector
        XMVECTOR vNormToGrav = pSrcSkeleton->vNormalToGravity;

        // Check for an invalid up vector (we will synthesize it from
        // the floor plane if that data is present). If we can't get an up
        // vector, we default to 0.0, 1.0, 0.0 instead.
        if ( fabs(vNormToGrav.x) < FLT_EPSILON &&
             fabs(vNormToGrav.y) < FLT_EPSILON &&
             fabs(vNormToGrav.z) < FLT_EPSILON )
        {
            vNormToGrav = vUp;
        }

        // Calculate running average of vector
        vAverageNormalToGravity = XMVectorLerp( vAverageNormalToGravity, vNormToGrav, 0.1f );

        // Generate the leveling matrix and apply it to all points on any skeletons
        // which are currently being tracked. 
        XMMATRIX matLevel = NuiTransformMatrixLevel( vAverageNormalToGravity );

        for ( INT i = 0 ; i < NUI_SKELETON_COUNT; i++ )
        {
            const NUI_SKELETON_DATA* pSkeletonData = &pSrcSkeleton->SkeletonData[ i ];
            XMVECTOR vSpine = pSkeletonData->SkeletonPositions[ NUI_SKELETON_POSITION_SPINE ];

            if ( pSkeletonData->eTrackingState != NUI_SKELETON_TRACKED )
            {
                vAverageSpine[ i ] = XMVectorZero();
                continue;
            }
            else
            {
                UINT uCompareResults;
                XMVectorEqualR( &uCompareResults, XMVectorZero(), vAverageSpine[ i ] );

                // if still set to zero, then start the running average
                if( XMComparisonAllTrue( uCompareResults ) )
                {
                    vAverageSpine[ i ] = vSpine;
                }
            }

            // Running average of spine
            vAverageSpine[ i ] = XMVectorLerp( vAverageSpine[ i ], vSpine, 0.1f );

            XMFLOAT4 fAverageSpine;
            XMStoreFloat4( &fAverageSpine, vAverageSpine[ i ] );
            XMMATRIX matTranslateToOrigin = XMMatrixTranslation( -fAverageSpine.x, 0, -fAverageSpine.z );
            XMMATRIX matTranslateFromOrigin = XMMatrixTranslation( fAverageSpine.x, 0, fAverageSpine.z );
            XMMATRIX matTransformation = matTranslateToOrigin * matLevel * matTranslateFromOrigin;

            for ( UINT j = 0; j < NUI_SKELETON_POSITION_COUNT; j++ )
            {
                pDstSkeleton->SkeletonData[ i ].SkeletonPositions[ j ] = XMVector3Transform( pSkeletonData->SkeletonPositions[ j ], matLevel );
            }
        }
    }