void Ply::calculate_normals()
{
    kvs::ValueArray<kvs::UInt32> counter( m_nverts );
    counter.fill( 0 );

    m_normals.allocate( m_nverts * 3 );
    const kvs::UInt32* pconnections = m_connections.data();
    const kvs::Real32* pcoords = m_coords.data();
    for ( size_t i = 0; i < m_nfaces; i++ )
    {
        // Calculate normal vector for each triangles.
        const kvs::UInt32 index0 = *(pconnections++);
        const kvs::UInt32 index1 = *(pconnections++);
        const kvs::UInt32 index2 = *(pconnections++);

        const kvs::Vector3f v0( pcoords + 3 * index0 );
        const kvs::Vector3f v1( pcoords + 3 * index1 );
        const kvs::Vector3f v2( pcoords + 3 * index2 );
        const kvs::Vector3f normal = ( ( v1 - v0 ).cross( v2 - v1 ) ).normalized();

        // Sum of the normal vectors of the adjacent triangles for the vertex.
        m_normals[ 3 * index0 + 0 ] = normal.x();
        m_normals[ 3 * index0 + 1 ] = normal.y();
        m_normals[ 3 * index0 + 2 ] = normal.z();
        counter[ index0 ] += 1;

        m_normals[ 3 * index1 + 0 ] = normal.x();
        m_normals[ 3 * index1 + 1 ] = normal.y();
        m_normals[ 3 * index1 + 2 ] = normal.z();
        counter[ index1 ] += 1;

        m_normals[ 3 * index2 + 0 ] = normal.x();
        m_normals[ 3 * index2 + 1 ] = normal.y();
        m_normals[ 3 * index2 + 2 ] = normal.z();
        counter[ index2 ] += 1;
    }

    for ( size_t i = 0; i < m_nverts; i++ )
    {
        if ( counter[i] == 0 ) continue;
        m_normals[ 3 * i + 0 ] /= static_cast<kvs::Real32>( counter[i] );
        m_normals[ 3 * i + 1 ] /= static_cast<kvs::Real32>( counter[i] );
        m_normals[ 3 * i + 2 ] /= static_cast<kvs::Real32>( counter[i] );
    }
}