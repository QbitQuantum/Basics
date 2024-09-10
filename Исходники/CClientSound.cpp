void CClientSound::Process3D ( CVector vecPosition, CVector vecLookAt )
{
    if ( !m_b3D ) return;

    // Update our position/rotation if we're attached
    DoAttaching ();

    if ( m_pSound )
    {
        // Pan
        CVector vecLook = vecLookAt - vecPosition;
        CVector vecSound = m_vecPosition - vecPosition;
        vecLook.fZ = vecSound.fZ = 0.0f;
        vecLook.Normalize ();
        vecSound.Normalize ();

        vecLook.CrossProduct ( &vecSound );
        // The length of the cross product (which is simply fZ in this case)
        // is equal to the sine of the angle between the vectors
        float fPan = vecLook.fZ;
        if ( fPan < -1.0f + SOUND_PAN_THRESHOLD )
            fPan = -1.0f + SOUND_PAN_THRESHOLD;
        else if ( fPan > 1.0f - SOUND_PAN_THRESHOLD )
            fPan = 1.0f - SOUND_PAN_THRESHOLD;

        m_pSound->setPan ( fPan );

        // Volume
        float fDistance = DistanceBetweenPoints3D ( vecPosition, m_vecPosition );
        float fSilenceDistance = m_fMinDistance * 20.0f;
        float fVolume = 1.0;

        if ( fDistance <= m_fMinDistance )
        {
            fVolume = 1.0f;
        }
        else if ( fDistance >= fSilenceDistance )
        {
            fVolume = 0.0f;
        }
        else
        {
            float fLinear = (fSilenceDistance - fDistance) / fSilenceDistance;
            fVolume = sqrt ( fLinear ) * fLinear;
        }

        m_pSound->setVolume ( m_fVolume * fVolume );
    }
}