void CBassAudio::Process3D ( const CVector& vecPlayerPosition, const CVector& vecCameraPosition, const CVector& vecLookAt )
{
    assert ( m_b3D && m_pSound );

    float fDistance = DistanceBetweenPoints3D ( vecCameraPosition, m_vecPosition );
    if ( m_bPan )
    {
        // Limit panning when getting close to the min distance
        float fPanSharpness = UnlerpClamped ( m_fMinDistance, fDistance, m_fMinDistance * 2 );
        float fPanLimit = Lerp ( 0.35f, fPanSharpness, 1.0f );

        // Pan
        CVector vecLook = vecLookAt - vecCameraPosition;
        CVector vecSound = m_vecPosition - vecCameraPosition;
        vecLook.fZ = vecSound.fZ = 0.0f;
        vecLook.Normalize ();
        vecSound.Normalize ();

        vecLook.CrossProduct ( &vecSound );
        // The length of the cross product (which is simply fZ in this case)
        // is equal to the sine of the angle between the vectors
        float fPan = Clamp ( -fPanLimit, -vecLook.fZ, fPanLimit );

        BASS_ChannelSetAttribute( m_pSound, BASS_ATTRIB_PAN, fPan );
    }
    else
    {
        // Revert to middle.
        BASS_ChannelSetAttribute( m_pSound, BASS_ATTRIB_PAN, 0.0f );
    }

    // Volume
    float fDistDiff = m_fMaxDistance - m_fMinDistance;

    //Transform e^-x to suit our sound
    float fVolume;
    if ( fDistance <= m_fMinDistance )
        fVolume = 1.0f;
    else if ( fDistance >= m_fMaxDistance )
        fVolume = 0.0f;
    else
        fVolume = exp ( - ( fDistance - m_fMinDistance ) * ( CUT_OFF / fDistDiff ) );

    BASS_ChannelSetAttribute( m_pSound, BASS_ATTRIB_VOL, fVolume * m_fVolume );
}