//
// Make player 'orbit camera' rotate to face this point
//
void CClientCamera::SetOrbitTarget ( const CVector& vecPosition )
{
    if ( m_pCamera )
    {
        CClientEntity* pCameraTarget = GetTargetEntity ( );

        if ( pCameraTarget != nullptr )
        {
            CVector vecTargetPosition;
            pCameraTarget->GetPosition ( vecTargetPosition );
            if ( pCameraTarget->GetType () == CCLIENTPLAYER )
                vecTargetPosition.fZ += 0.6f;

            CVector vecDirection = vecPosition - vecTargetPosition;
            vecDirection.Normalize ();

            float fAngleHorz = -atan2 ( vecDirection.fX, vecDirection.fY ) - PI / 2;
            float fAngleVert = asin ( vecDirection.fZ );

            CCam* pCam = m_pCamera->GetCam ( m_pCamera->GetActiveCam () );
            pCam->SetDirection ( fAngleHorz, fAngleVert );
        }
    }
}