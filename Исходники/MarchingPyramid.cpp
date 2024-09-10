void MarchingPyramid::extract_surfaces_with_duplication(
    const kvs::UnstructuredVolumeObject* volume )
{
    // Calculated the coordinate data array and the normal vector array.
    std::vector<kvs::Real32> coords;
    std::vector<kvs::Real32> normals;

    const kvs::UInt32 ncells( volume->numberOfCells() );
    const kvs::UInt32* connections =
        static_cast<const kvs::UInt32*>( volume->connections().data() );

    // Extract surfaces.
    size_t index = 0;
    size_t local_index[5];
    for ( kvs::UInt32 cell = 0; cell < ncells; ++cell, index += 5 )
    {
        // Calculate the indices of the target cell.
        local_index[0] = connections[ index + 0 ];
        local_index[1] = connections[ index + 1 ];
        local_index[2] = connections[ index + 2 ];
        local_index[3] = connections[ index + 3 ];
        local_index[4] = connections[ index + 4 ];

        // Calculate the index of the reference table.
        size_t table_index = this->calculate_table_index<T>( local_index );
        if ( table_index == 0 ) continue;
        if ( table_index == 10 || table_index == 11 || table_index == 20 || table_index == 21 ){
            table_index = this->calculate_special_table_index<T>( local_index, table_index );
        }
        if ( table_index == 36 ) continue;

        // Calculate the triangle polygons.
        for ( size_t i = 0; MarchingPyramidTable::TriangleID[ table_index ][i] != -1; i += 3 )
        {
            // Refer the edge IDs from the TriangleTable by using the table_index.
            const int e0 = MarchingPyramidTable::TriangleID[table_index][i];
            const int e1 = MarchingPyramidTable::TriangleID[table_index][i+2];
            const int e2 = MarchingPyramidTable::TriangleID[table_index][i+1];

            // Determine vertices for each edge.
            const int v0 = local_index[MarchingPyramidTable::VertexID[e0][0]];
            const int v1 = local_index[MarchingPyramidTable::VertexID[e0][1]];

            const int v2 = local_index[MarchingPyramidTable::VertexID[e1][0]];
            const int v3 = local_index[MarchingPyramidTable::VertexID[e1][1]];

            const int v4 = local_index[MarchingPyramidTable::VertexID[e2][0]];
            const int v5 = local_index[MarchingPyramidTable::VertexID[e2][1]];

            // Calculate coordinates of the vertices which are composed
            // of the triangle polygon.
            const kvs::Vector3f vertex0( this->interpolate_vertex<T>( v0, v1 ) );
            coords.push_back( vertex0.x() );
            coords.push_back( vertex0.y() );
            coords.push_back( vertex0.z() );

            const kvs::Vector3f vertex1( this->interpolate_vertex<T>( v2, v3 ) );
            coords.push_back( vertex1.x() );
            coords.push_back( vertex1.y() );
            coords.push_back( vertex1.z() );

            const kvs::Vector3f vertex2( this->interpolate_vertex<T>( v4, v5 ) );
            coords.push_back( vertex2.x() );
            coords.push_back( vertex2.y() );
            coords.push_back( vertex2.z() );

            // Calculate a normal vector for the triangle polygon.
            const kvs::Vector3f normal( ( vertex1 - vertex0 ).cross( vertex2 - vertex0 ) );
            normals.push_back( normal.x() );
            normals.push_back( normal.y() );
            normals.push_back( normal.z() );
        } // end of loop-triangle
    } // end of loop-cell

    // Calculate the polygon color for the isolevel.
    const kvs::RGBColor color = this->calculate_color<T>();

    if( coords.size() > 0 ){
        SuperClass::setCoords( kvs::ValueArray<kvs::Real32>( coords ) );
        SuperClass::setColor( color );
        SuperClass::setNormals( kvs::ValueArray<kvs::Real32>( normals ) );
        SuperClass::setOpacity( 255 );
        SuperClass::setPolygonType( kvs::PolygonObject::Triangle );
        SuperClass::setColorType( kvs::PolygonObject::PolygonColor );
        SuperClass::setNormalType( kvs::PolygonObject::PolygonNormal );
    }
}