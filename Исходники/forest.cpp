Forest::Forest(Actor* parent, ForestDesc* desc) : Actor( parent )
{
    assert( desc );
    assert( desc->surface );
    assert( desc->assetName.length() );
    assert( desc->cache.length() );

    // copy descriptor
    _desc = *desc;    

    // load asset
    _asset = Gameplay::iEngine->createAsset( engine::atBinary, _desc.assetName.c_str() );

    // enumerate clumps
    callback::ClumpL clumps;    
    _asset->forAllClumps( callback::enumerateClumps, &clumps );
    assert( clumps.size() );

    // fill batch schemes
    Matrix4f clumpM;
    MatrixConversion trunkConversion;
    MatrixConversion canopyConversion;
    _canopyScheme.numLods = _trunkScheme.numLods = clumps.size();
    for( callback::ClumpI clumpI = clumps.begin(); clumpI != clumps.end(); clumpI++ )
    {
        // determine lod Id and check for consistency
        unsigned int lodId = getClumpLodId( *clumpI );
        if( _trunkScheme.lodGeometry[lodId] )
        {
            throw Exception( "Clump \"%s\" is a duplication of existing LOD!", (*clumpI)->getName() );
        }
        // fill schemes
        engine::IAtomic* trunkAtomic     = Gameplay::iEngine->getAtomic( *clumpI, Gameplay::iEngine->findFrame( (*clumpI)->getFrame(), "Trunk" ) ); assert( trunkAtomic );
        engine::IAtomic* canopyAtomic    = Gameplay::iEngine->getAtomic( *clumpI, Gameplay::iEngine->findFrame( (*clumpI)->getFrame(), "Canopy" ) ); assert( canopyAtomic );
        _trunkScheme.lodGeometry[lodId]  = trunkAtomic->getGeometry();        
        _canopyScheme.lodGeometry[lodId] = canopyAtomic->getGeometry();
        _trunkScheme.lodDistance[lodId] = _canopyScheme.lodDistance[lodId] = _desc.lodDistance[lodId];
        // calculate conversions for nearest LOD
        if( lodId == 0 )
        {
            clumpM = (*clumpI)->getFrame()->getLTM();
            trunkConversion.setup( clumpM, trunkAtomic->getFrame()->getLTM() );
            canopyConversion.setup( clumpM, canopyAtomic->getFrame()->getLTM() );
        }
    }

    _trunkScheme.flags = _canopyScheme.flags = 0;

    // check schemes
    assert( _trunkScheme.isValid() );
    assert( _canopyScheme.isValid() );

    // create full cache names
    std::string instanceCache  = _desc.cache; instanceCache  += ".matrices";
    std::string trunkBspCache  = _desc.cache; trunkBspCache  += ".trunk";
    std::string canopyBspCache = _desc.cache; canopyBspCache += ".canopy";

    // try to load forest from cache
    IResource* resource = getCore()->getResource( instanceCache.c_str(), "rb" );
    if( resource )
    {
        unsigned int numTrees;
        fread( &numTrees, sizeof(unsigned int), 1, resource->getFile() );
        _treeMatrix.resize( numTrees );
        fread( &_treeMatrix[0], sizeof(Matrix4f), numTrees, resource->getFile() );
        resource->release();
    }
    else
    {
        // obtain surface properties
        Matrix4f ltm = _desc.surface->getFrame()->getLTM();
        engine::IGeometry* geometry = _desc.surface->getGeometry();
        engine::Mesh* mesh = geometry->createMesh();

        float preservedDistance = _desc.collScale * ( geometry->getAABBSup() - geometry->getAABBInf() ).length();

        // iterate surface triangles
        Vector3f vertex[3];
        Vector3f edge[3];
        Vector3f edgeN[2];
        Vector3f normal;
        Vector3f pos;
        float cosA, sinA, angle, square, probability, scale;
        unsigned int i,j,numTreesInTriangle;
        Matrix4f instanceM;    
        for( i=0; i<mesh->numTriangles; i++ )
        {
            // transform triangle vertices to world space
            vertex[0] = Gameplay::iEngine->transformCoord( mesh->vertices[mesh->triangles[i].vertexId[0]], ltm );
            vertex[1] = Gameplay::iEngine->transformCoord( mesh->vertices[mesh->triangles[i].vertexId[1]], ltm );
            vertex[2] = Gameplay::iEngine->transformCoord( mesh->vertices[mesh->triangles[i].vertexId[2]], ltm );
            // calculate triangle square value...
            edge[0] = vertex[1] - vertex[0];
            edge[1] = vertex[2] - vertex[0];
            edge[2] = vertex[2] - vertex[1];
            edgeN[0] = edge[0]; edgeN[0].normalize();
            edgeN[1] = edge[1]; edgeN[1].normalize();
            normal.cross( edgeN[0], edgeN[1] );
            cosA = Vector3f::dot( edgeN[0], edgeN[1] );
            if( cosA > 1.0f ) angle = 0.0f; 
            else if( cosA < -1.0f ) angle = 180; 
            else angle = acosf( cosA );
            sinA = sin( angle );
            square = 0.5f * edge[0].length() * edge[1].length() * sinA / 10000.0f;
            // obtain number of particles in this triangle
            numTreesInTriangle = unsigned int( square * _desc.density );
            if( !numTreesInTriangle )
            {
                // include probability method to decide to place grass on to this triangle
                probability = square / ( 1 / _desc.density );
                assert( probability <= 1.0f );
                if( probability > 0 && getCore()->getRandToolkit()->getUniform( 0, 1 ) <= probability ) numTreesInTriangle++;
            }
            // generate trees
            for( j=0; j<numTreesInTriangle; j++ )
            {
                // generate scale
                scale = getCore()->getRandToolkit()->getUniform( _desc.minScale, _desc.maxScale );
                // generate coordinate
                pos = generateRandomPosition( vertex, edge );                
                // generate matrix
                instanceM.set(
                    clumpM[0][0] * scale, clumpM[0][1] * scale, clumpM[0][2] * scale, 0.0f,
                    clumpM[1][0] * scale, clumpM[1][1] * scale, clumpM[1][2] * scale, 0.0f,
                    clumpM[2][0] * scale, clumpM[2][1] * scale, clumpM[2][2] * scale, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f
                );
                instanceM = Gameplay::iEngine->rotateMatrix( instanceM, Vector3f(0,1,0), getCore()->getRandToolkit()->getUniform(0,360) );
                instanceM[3][0] = pos[0];
                instanceM[3][1] = pos[1];
                instanceM[3][2] = pos[2];
                _treeMatrix.push_back( instanceM );
            }
            Scene::progressCallback( 
                Gameplay::iLanguage->getUnicodeString(844),
                float( i ) / float( mesh->numTriangles ),
                getScene()
            );
        }

        // release temporary resources
        Gameplay::iEngine->releaseMesh( mesh );

        // write solution
        ccor::IResource* resource = getCore()->getResource( instanceCache.c_str(), "wb" );
        unsigned int numTrees = _treeMatrix.size();
        fwrite( &numTrees, sizeof(unsigned int), 1, resource->getFile() );
        fwrite( &_treeMatrix[0], sizeof(Matrix4f), numTrees, resource->getFile() );
        resource->release();
    }
    
    // build batches
    _trunkBatch  = Gameplay::iEngine->createBatch( _treeMatrix.size(), &_trunkScheme ); assert( _trunkBatch );
    _canopyBatch = Gameplay::iEngine->createBatch( _treeMatrix.size(), &_canopyScheme ); assert( _canopyBatch );
    // fill batches
    for( unsigned int i=0; i<_treeMatrix.size(); i++ )
    {
        _trunkBatch->setMatrix( i, trunkConversion.convert( _treeMatrix[i] ) );
        _canopyBatch->setMatrix( i, canopyConversion.convert( _treeMatrix[i] ) );
    }

    // create spatial acceleration structures BSP trees
    _trunkBatch->createBatchTree( _desc.bspLeafSize, trunkBspCache.c_str() );
    _canopyBatch->createBatchTree( _desc.bspLeafSize, canopyBspCache.c_str() );
    
    // add batches to scene
    getScene()->getStage()->add( _trunkBatch );
    getScene()->getStage()->add( _canopyBatch );

    // add layers to scene
    if( _desc.layers )
    {
        getScene()->getStage()->add( _desc.layers );
    }

    // set no sound
    _rustleSound = _squeakSound = NULL;
}