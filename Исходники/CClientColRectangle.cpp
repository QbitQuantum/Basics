//
// Draw wireframe rectangle
//
void CClientColRectangle::DebugRender ( const CVector& vecPosition, float fDrawRadius )
{
    CVector vecBase ( m_vecPosition.fX, m_vecPosition.fY, vecPosition.fZ - fDrawRadius );
    CVector vecOrigin ( m_vecPosition.fX + m_vecSize.fX * 0.5f, m_vecPosition.fY + m_vecSize.fY * 0.5f, vecPosition.fZ );
    CVector vecSize ( m_vecSize.fX, m_vecSize.fY, fDrawRadius * 2.f );

    SColorARGB color ( 128, 255, 0, 255 );
    float fLineWidth = 4.f + pow ( std::max ( m_vecSize.fX, m_vecSize.fY ) * 0.5f, 0.5f );
    CGraphicsInterface* pGraphics = g_pCore->GetGraphics ();

    // Don't draw a few end slices to show it goes on for ever
    int iSkipEndSlicesZ = 4;

    // Calc required detail level
    uint uiNumSlicesX = std::max ( 2, Round ( sqrt ( vecSize.fX ) * 1.5f ) );
    uint uiNumSlicesY = std::max ( 2, Round ( sqrt ( vecSize.fY ) * 1.5f ) );
    uint uiNumSlicesZ = std::max ( 2 + iSkipEndSlicesZ * 2, Round ( sqrt ( vecSize.fZ ) * 2.0f ) );

    // Draw Slices Z
    {
        static const CVector cornerPoints[] = { CVector( 0, 0, 1 ), CVector( 1, 0, 1 ), CVector( 1, 1, 1 ), CVector( 0, 1, 1 ) };

        CVector vecMult = vecSize;
        CVector vecAdd = vecBase + CVector ( 0, 0, 4 ); // Extra bit so a slice is on the same Z coord as the camera

        for ( uint s = iSkipEndSlicesZ ; s < uiNumSlicesZ - iSkipEndSlicesZ ; s++ )
        {
            vecMult.fZ = vecSize.fZ * ( s / (float)( uiNumSlicesZ - 1 ) );
            for ( uint i = 0 ; i < NUMELMS( cornerPoints ) ; i++ )
            {
                const CVector& vecBegin = cornerPoints [ i ] * vecMult + vecAdd;
                const CVector& vecEnd = cornerPoints [ ( i + 1 ) % 4 ] * vecMult + vecAdd;
                pGraphics->DrawLine3DQueued ( vecBegin, vecEnd, fLineWidth, color, false );
            }
        }
    }

    // Draw Slices Y
    {
        static const CVector cornerPoints[] = { CVector( 0, 1, 0 ), CVector( 1, 1, 0 ), CVector( 1, 1, 1 ), CVector( 0, 1, 1 ) };

        CVector vecMult = vecSize;
        CVector vecAdd = vecBase;

        for ( uint s = 0 ; s < uiNumSlicesY ; s++ )
        {
            vecMult.fY = vecSize.fY * ( s / (float)( uiNumSlicesY - 1 ) );
            for ( uint i = 0 ; i < NUMELMS( cornerPoints ) ; i++ )
            {
                if ( !(i & 1) )
                    continue;   // No end cap
                const CVector& vecBegin = cornerPoints [ i ] * vecMult + vecAdd;
                const CVector& vecEnd = cornerPoints [ ( i + 1 ) % 4 ] * vecMult + vecAdd;
                pGraphics->DrawLine3DQueued ( vecBegin, vecEnd, fLineWidth, color, false );
            }
        }
    }

    // Draw Slices X
    {
        static const CVector cornerPoints[] = { CVector( 1, 0, 0 ), CVector( 1, 1, 0 ), CVector( 1, 1, 1 ), CVector( 1, 0, 1 ) };

        CVector vecMult = vecSize;
        CVector vecAdd = vecBase;

        for ( uint s = 0 ; s < uiNumSlicesX ; s++ )
        {
            vecMult.fX = vecSize.fX * ( s / (float)( uiNumSlicesX - 1 ) );
            for ( uint i = 0 ; i < NUMELMS( cornerPoints ) ; i++ )
            {
                if ( !(i & 1) )
                    continue;   // No end cap
                const CVector& vecBegin = cornerPoints [ i ] * vecMult + vecAdd;
                const CVector& vecEnd = cornerPoints [ ( i + 1 ) % 4 ] * vecMult + vecAdd;
                pGraphics->DrawLine3DQueued ( vecBegin, vecEnd, fLineWidth, color, false );
            }
        }
    }
}