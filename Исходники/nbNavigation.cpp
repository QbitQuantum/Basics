    /*!
     Build a NAVIGATION mesh from an OBJ mesh index. Usually this OBJMESH is either a collision map
     or a mesh that have been built especially for navigation.
     
     \param[in,out] navigation A valid NAVIGATION structure pointer.
     \param[in] obj A valid OBJ structure pointer.
     \param[in] mesh_index The mesh index of the OBJMESH to use to create the NAVIGATION mesh.
     
     \return Return 1 if the NAVIGATION mesh have been generated successfully, else this function will return 0.
     */
    unsigned char NAVIGATION_build( NAVIGATION *navigation, Object *obj, unsigned int mesh_index )
    {
        unsigned int i = 0,
        j = 0,
        k = 0,
        triangle_count = 0;
        
        int *indices = NULL;
        
        Mesh *objmesh = obj->meshList[ mesh_index ];
        
//        vec3 *vertex_array = ( vec3 * ) malloc( objmesh->n_objvertexdata * sizeof( vec3 ) ),
        vec3 *vertex_array = ( vec3 * ) malloc( objmesh->uniqueVertexUVIndexList.size() * sizeof( vec3 ) ),
        *vertex_start = vertex_array;
        
        rcHeightfield *rcheightfield;
        
        rcCompactHeightfield *rccompactheightfield;
        
        rcContourSet *rccontourset;
        
        rcPolyMesh *rcpolymesh;
        
        rcPolyMeshDetail *rcpolymeshdetail;
        
        
        while( i != objmesh->uniqueVertexUVIndexList.size() )
        {
            
            
            memcpy( vertex_array,
                   &obj->vertexMgr.uniqueVertexList[objmesh->uniqueVertexUVIndexList[i].vertexIndex],
                   sizeof( vec3 ) );
            
            *vertex_array = vertex_array->toRecast();
            
//            vec3_to_recast( vertex_array );
            
            ++vertex_array;
            ++i;
        }
        
//        while( i != objmesh->n_objvertexdata )
//        {
//            memcpy( vertex_array,
//                   &obj->indexed_vertex[ objmesh->objvertexdata[ i ].vertex_index ],
//                   sizeof( vec3 ) );
//            
//            vec3_to_recast( vertex_array );
//            
//            ++vertex_array;
//            ++i;
//        }
        
            triangle_count += objmesh->vertexIndexList.size();
            
            indices = ( int * ) realloc( indices, triangle_count * sizeof( int ) );
            
            j = 0;
            while( j != objmesh->vertexIndexList.size() )
            {
                indices[ k ] = objmesh->vertexIndexList[ j ];
                
                ++k;
                ++j;
            }
//
//        i = 0;
//        while( i != objmesh->n_objtrianglelist )
//        {
//            triangle_count += objmesh->objtrianglelist[ i ].n_indice_array;
//            
//            indices = ( int * ) realloc( indices, triangle_count * sizeof( int ) );
//            
//            j = 0;
//            while( j != objmesh->objtrianglelist[ i ].n_indice_array )
//            {
//                indices[ k ] = objmesh->objtrianglelist[ i ].indice_array[ j ];
//                
//                ++k;
//                ++j;
//            }
//            
//            ++i;
//        }
        
        triangle_count /= 3;
        
        rcConfig rcconfig;
        
        memset( &rcconfig, 0, sizeof( rcConfig ) );
        
        rcconfig.cs						= navigation->navigationconfiguration.cell_size;
        rcconfig.ch						= navigation->navigationconfiguration.cell_height;
        rcconfig.walkableHeight			= ( int )ceilf ( navigation->navigationconfiguration.agent_height / rcconfig.ch );
        rcconfig.walkableRadius			= ( int )ceilf ( navigation->navigationconfiguration.agent_radius / rcconfig.cs );
        rcconfig.walkableClimb			= ( int )floorf( navigation->navigationconfiguration.agent_max_climb / rcconfig.ch );
        rcconfig.walkableSlopeAngle		= navigation->navigationconfiguration.agent_max_slope;
        rcconfig.minRegionSize			= ( int )rcSqr( navigation->navigationconfiguration.region_min_size );
        rcconfig.mergeRegionSize		= ( int )rcSqr( navigation->navigationconfiguration.region_merge_size );
        rcconfig.maxEdgeLen				= ( int )( navigation->navigationconfiguration.edge_max_len / rcconfig.cs );
        rcconfig.maxSimplificationError = navigation->navigationconfiguration.edge_max_error;
        rcconfig.maxVertsPerPoly		= ( int )navigation->navigationconfiguration.vert_per_poly;
        rcconfig.detailSampleDist		= rcconfig.cs * navigation->navigationconfiguration.detail_sample_dst;
        rcconfig.detailSampleMaxError   = rcconfig.ch * navigation->navigationconfiguration.detail_sample_max_error;
        
        
        rcCalcBounds( ( float * )vertex_start,
                     (int)objmesh->uniqueVertexUVIndexList.size(),
//                     objmesh->n_objvertexdata,
                     rcconfig.bmin,
                     rcconfig.bmax );
        
        
        rcCalcGridSize(  rcconfig.bmin,
                       rcconfig.bmax,
                       rcconfig.cs,
                       &rcconfig.width,
                       &rcconfig.height );
        
        
        rcheightfield = rcAllocHeightfield();
        
        rcCreateHeightfield( *rcheightfield,
                            rcconfig.width,
                            rcconfig.height,
                            rcconfig.bmin,
                            rcconfig.bmax,
                            rcconfig.cs,
                            rcconfig.ch );
        
        
        navigation->triangle_flags = new unsigned char[ triangle_count ];
        
        memset( navigation->triangle_flags, 0, triangle_count * sizeof( unsigned char ) );
        
        rcMarkWalkableTriangles( rcconfig.walkableSlopeAngle,
                                ( float * )vertex_start,
                                (int)objmesh->uniqueVertexUVIndexList.size(),
//                                objmesh->n_objvertexdata,
                                indices,
                                triangle_count,
                                navigation->triangle_flags );
        
        
        rcRasterizeTriangles( ( float * )vertex_start,
                             (int)objmesh->uniqueVertexUVIndexList.size(),
//                             objmesh->n_objvertexdata,
                             indices,
                             navigation->triangle_flags,
                             triangle_count,
                             *rcheightfield,
                             rcconfig.walkableClimb );
        
        
        delete []navigation->triangle_flags;
        navigation->triangle_flags = NULL;
        
        free( vertex_start );
        free( indices      );
        
        
        rcFilterLowHangingWalkableObstacles(  rcconfig.walkableClimb,
                                            *rcheightfield );
        
        
        rcFilterLedgeSpans(  rcconfig.walkableHeight,
                           rcconfig.walkableClimb,
                           *rcheightfield );
        
        
        rcFilterWalkableLowHeightSpans(  rcconfig.walkableHeight,
                                       *rcheightfield );
        
        
        rccompactheightfield = rcAllocCompactHeightfield();
        
        rcBuildCompactHeightfield( rcconfig.walkableHeight,
                                  rcconfig.walkableClimb,
                                  RC_WALKABLE,
                                  *rcheightfield,
                                  *rccompactheightfield );
        
        rcFreeHeightField( rcheightfield );
        rcheightfield = NULL;
        
        rcErodeArea( RC_WALKABLE_AREA,
                    rcconfig.walkableRadius,
                    *rccompactheightfield );
        
        
        rcBuildDistanceField( *rccompactheightfield );
        
        
        rcBuildRegions( *rccompactheightfield,
                       rcconfig.borderSize,
                       rcconfig.minRegionSize,
                       rcconfig.mergeRegionSize );
        
        
        rccontourset = rcAllocContourSet();
        
        rcBuildContours( *rccompactheightfield,
                        rcconfig.maxSimplificationError,
                        rcconfig.maxEdgeLen,
                        *rccontourset );
        
        
        rcpolymesh = rcAllocPolyMesh();
        
        rcBuildPolyMesh( *rccontourset,
                        rcconfig.maxVertsPerPoly,
                        *rcpolymesh );
        
        
        rcpolymeshdetail = rcAllocPolyMeshDetail();
        
        rcBuildPolyMeshDetail( *rcpolymesh,
                              *rccompactheightfield,
                              rcconfig.detailSampleDist,
                              rcconfig.detailSampleMaxError,
                              *rcpolymeshdetail );
        
        
        rcFreeCompactHeightfield( rccompactheightfield );
        rccompactheightfield = NULL;
        
        rcFreeContourSet( rccontourset );
        rccontourset = NULL;
        
        
        if( rcconfig.maxVertsPerPoly <= DT_VERTS_PER_POLYGON )
        {
            dtNavMeshCreateParams dtnavmeshcreateparams;
            
            unsigned char *nav_data = NULL;
            
            int nav_data_size = 0;
            
            i = 0;
            while( i != rcpolymesh->npolys )
            {
                if( rcpolymesh->areas[ i ] == RC_WALKABLE_AREA )
                {
                    rcpolymesh->areas[ i ] = 0;
                    rcpolymesh->flags[ i ] = 0x01;
                }
                
                ++i;
            }
            
            
            memset( &dtnavmeshcreateparams, 0, sizeof( dtNavMeshCreateParams ) );
            
            dtnavmeshcreateparams.verts			   = rcpolymesh->verts;
            dtnavmeshcreateparams.vertCount		   = rcpolymesh->nverts;
            dtnavmeshcreateparams.polys			   = rcpolymesh->polys;
            dtnavmeshcreateparams.polyAreas		   = rcpolymesh->areas;
            dtnavmeshcreateparams.polyFlags		   = rcpolymesh->flags;
            dtnavmeshcreateparams.polyCount		   = rcpolymesh->npolys;
            dtnavmeshcreateparams.nvp			   = rcpolymesh->nvp;
            
            dtnavmeshcreateparams.detailMeshes	   = rcpolymeshdetail->meshes;
            dtnavmeshcreateparams.detailVerts	   = rcpolymeshdetail->verts;
            dtnavmeshcreateparams.detailVertsCount = rcpolymeshdetail->nverts;
            dtnavmeshcreateparams.detailTris       = rcpolymeshdetail->tris;
            dtnavmeshcreateparams.detailTriCount   = rcpolymeshdetail->ntris;
            
            dtnavmeshcreateparams.walkableHeight   = navigation->navigationconfiguration.agent_height;
            dtnavmeshcreateparams.walkableRadius   = navigation->navigationconfiguration.agent_radius;
            dtnavmeshcreateparams.walkableClimb    = navigation->navigationconfiguration.agent_max_climb;
            
            rcVcopy( dtnavmeshcreateparams.bmin, rcpolymesh->bmin );
            rcVcopy( dtnavmeshcreateparams.bmax, rcpolymesh->bmax );
            
            dtnavmeshcreateparams.cs = rcconfig.cs;
            dtnavmeshcreateparams.ch = rcconfig.ch;
            
            
            dtCreateNavMeshData( &dtnavmeshcreateparams,
                                &nav_data,
                                &nav_data_size );
            
            if( !nav_data ) return 0;
            
            navigation->dtnavmesh = dtAllocNavMesh();
            
            navigation->dtnavmesh->init( nav_data,
                                        nav_data_size,
                                        DT_TILE_FREE_DATA,
                                        NAVIGATION_MAX_NODE );
            
            rcFreePolyMesh( rcpolymesh );
            rcpolymesh = NULL;
            
            rcFreePolyMeshDetail( rcpolymeshdetail );
            rcpolymeshdetail = NULL;
            
            return 1;
        }
        
        return 0;
    }