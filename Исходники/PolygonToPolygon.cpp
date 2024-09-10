/*===========================================================================*/
void PolygonToPolygon::calculate_triangle_normals( void )
{
    const size_t nvertices = SuperClass::nvertices();
    const size_t npolygons = SuperClass::nconnections();
    const float* p_coords = SuperClass::coords().pointer();
    const unsigned int* p_connections = SuperClass::connections().pointer();

    kvs::ValueArray<float> normals( 3 * nvertices );
    normals.fill( 0x00 );

    for ( size_t i = 0; i < npolygons; i++ )
    {
        size_t index[3];
        kvs::Vector3f vertex[3];
        for ( size_t j = 0; j < 3; j++ )
        {
            index[j] = p_connections[ 3 * i + j ];
            vertex[j] = kvs::Vector3f( p_coords + 3 * index[j] );
        }

        const kvs::Vector3f normal( ( vertex[1] - vertex[0] ).cross( vertex[2] - vertex[0] ) );
        for ( size_t j = 0; j < 3; j++ )
        {
            normals[ 3 * index[j]     ] += normal.x();
            normals[ 3 * index[j] + 1 ] += normal.y();
            normals[ 3 * index[j] + 2 ] += normal.z();
        }
    }

    // Normalize normals.
    const float* p_normals = normals.pointer();
    for ( size_t i = 0; i < nvertices; i++ )
    {
        kvs::Vector3f normal( p_normals + i * 3 );
        normal.normalize();
        normals[ i * 3     ] = normal.x();
        normals[ i * 3 + 1 ] = normal.y();
        normals[ i * 3 + 2 ] = normal.z();
    }

    SuperClass::setNormals( normals );
    SuperClass::setNormalType( kvs::PolygonObject::VertexNormal );
}