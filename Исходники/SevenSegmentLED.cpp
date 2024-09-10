void OneSegment::build_segment_coord(
    const kvs::Vector3f& center,
    const float length,
    const float width,
    const float offset,
    const float left_ratio,
    const float right_ratio,
    const float rotate_theta )
{
    m_coords.allocate( 3 * 6 );

    // Set const z coord.
    for ( size_t i = 2; i < 18; i += 3 ) m_coords[i] = center.z();

    const float half_length = length / 2;

    m_coords[ 0] = - ( half_length + left_ratio * width - offset );
    m_coords[ 1] = - left_ratio * width;

    m_coords[ 3] = - ( half_length - width - offset );
    m_coords[ 4] = width;

    m_coords[ 6] = - ( half_length - ( 1.0f - 2 * left_ratio ) * width - offset );
    m_coords[ 7] = - width;

    m_coords[ 9] = ( half_length - width - offset );
    m_coords[10] = width;

    m_coords[12] = ( half_length - ( 1.0f - 2 * right_ratio ) * width - offset );
    m_coords[13] = - width;

    m_coords[15] = ( half_length + right_ratio * width - offset );
    m_coords[16] = - right_ratio * width;

    for ( size_t i = 0; i < 6; i++ )
    {
        const float theta = kvs::Math::Deg2Rad( rotate_theta );
        const float x = m_coords[ i * 3 + 0 ];
        const float y = m_coords[ i * 3 + 1 ];
        m_coords[ i * 3 + 0 ] = center.x() + cosf( theta ) * x + sinf( theta ) * y;
        m_coords[ i * 3 + 1 ] = center.y() - sinf( theta ) * x + cosf( theta ) * y;
    }
}