Enclosure::Enclosure(engine::IClump* clump, float delay)
{
    _clump = clump;
    _clump->getFrame()->translate( Vector3f( 0,0,0 ) );
    _clump->getFrame()->getLTM();

    _delay = delay;

    _ray = Gameplay::iEngine->createRayIntersection();
    _sphere = Gameplay::iEngine->createSphereIntersection();
    
    callback::Locator locator;
    locator.targetName = _clump->getName();
    locator.target = NULL;
    _clump->forAllAtomics( callback::locateAtomic, &locator );    
    _collisionAtomic = reinterpret_cast<engine::IAtomic*>( locator.target );
    assert( _collisionAtomic );

    engine::IGeometry* geometry = _collisionAtomic->getGeometry();
    engine::IShader* shader;
    unsigned int numFaces = geometry->getNumFaces();
    Vector3f vertex[3];
    Vector3f normal;
    bool flag;
    unsigned int i,j;

    // enumerate normals of wall faces 
    for( i=0; i<numFaces; i++ )
    {
        geometry->getFace( i, vertex[0], vertex[1], vertex[2], &shader );
        if( strcmp( shader->getName(), "EnclosureFloor" ) != 0 )
        {
            normal.cross( vertex[1]-vertex[0], vertex[2]-vertex[0] );
            normal.normalize();
            // check this normal was enumerated
            flag = false;
            for( j=0; j<_wallNormals.size(); j++ )
            {
                if( Vector3f::dot( _wallNormals[j], normal ) > 0.999f )
                {
                    flag = true;
                    break;
                }
            }
            if( !flag ) _wallNormals.push_back( normal );
        }
    }

    // enumerate position markers (all atomics under enclosure care)
    callback::AtomicL atomicL;
    _clump->forAllAtomics( callback::enumerateAtomics, &atomicL );    
    for( callback::AtomicI atomicI=atomicL.begin(); atomicI!=atomicL.end(); atomicI++ )
    {   
        if( (*atomicI) != _collisionAtomic )
        {
            _markers.push_back( (*atomicI)->getFrame() );
        }
    }

    /*
    // check number of path points (limit of 2)
    unsigned int numPathPoints = 0;
    for( unsigned int i=0; i<getNumMarkers(); i++ )
    {
        if( getMarkerFlags( i ) & mtPath ) numPathPoints++;
    }
    if( numPathPoints > 2 )
    {
        throw Exception( "Too many pathpoints in enclosure %s", clump->getName() );
    }
    */
}