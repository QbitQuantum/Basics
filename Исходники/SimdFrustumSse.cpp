/// Test whether this frustum intersects a given axis-aligned bounding box in world space.
///
/// @param[in] rBox  Box to test.
///
/// @return  True if the box intersects this frustum, false if not.
bool Helium::Simd::Frustum::Intersects( const AaBox& rBox ) const
{
    Helium::Simd::Register boxMinVec = rBox.GetMinimum().GetSimdVector();
    Helium::Simd::Register boxMaxVec = rBox.GetMaximum().GetSimdVector();

    Helium::Simd::Register boxX0 = _mm_shuffle_ps( boxMinVec, boxMinVec, _MM_SHUFFLE( 0, 0, 0, 0 ) );
    Helium::Simd::Register boxX1 = _mm_shuffle_ps( boxMaxVec, boxMaxVec, _MM_SHUFFLE( 0, 0, 0, 0 ) );
    Helium::Simd::Register boxY = _mm_shuffle_ps( boxMinVec, boxMaxVec, _MM_SHUFFLE( 1, 1, 1, 1 ) );
    Helium::Simd::Register boxZ = _mm_unpackhi_ps( boxMinVec, boxMaxVec );
    boxZ = _mm_movelh_ps( boxZ, boxZ );

    PlaneSoa plane;
    Vector3Soa points( boxX0, boxY, boxZ );
    Helium::Simd::Register zeroVec = Helium::Simd::LoadZeros();

    size_t planeCount = ( m_bInfiniteFarClip ? PLANE_FAR : PLANE_MAX );
    for( size_t planeIndex = 0; planeIndex < planeCount; ++planeIndex )
    {
        plane.Load1Splat(
            m_planeA + planeIndex,
            m_planeB + planeIndex,
            m_planeC + planeIndex,
            m_planeD + planeIndex );

        points.m_x = boxX0;
        Helium::Simd::Mask containsPoints0 = Helium::Simd::GreaterEqualsF32( plane.GetDistance( points ), zeroVec );

        points.m_x = boxX1;
        Helium::Simd::Mask containsPoints1 = Helium::Simd::GreaterEqualsF32( plane.GetDistance( points ), zeroVec );

        int resultMask = _mm_movemask_ps( Helium::Simd::Or( containsPoints0, containsPoints1 ) );
        if( resultMask == 0 )
        {
            return false;
        }
    }

    return true;
}