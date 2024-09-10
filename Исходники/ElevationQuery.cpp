bool
ElevationQuery::getElevationImpl(const GeoPoint& point, /* abs */
                                 double&         out_elevation,
                                 double          desiredResolution,
                                 double*         out_actualResolution)
{
    // assertion.
    if ( !point.isAbsolute() )
    {
        OE_WARN << LC << "Assertion failure; input must be absolute" << std::endl;
        return false;
    }

    osg::Timer_t begin = osg::Timer::instance()->tick();

    // first try the terrain patches.
    if ( _patchLayers.size() > 0 )
    {
        osgUtil::IntersectionVisitor iv;

        for(std::vector<ModelLayer*>::iterator i = _patchLayers.begin(); i != _patchLayers.end(); ++i)
        {
            // find the scene graph for this layer:
            osg::Node* node = (*i)->getSceneGraph( _mapf.getUID() );
            if ( node )
            {
                // configure for intersection:
                osg::Vec3d surface;
                point.toWorld( surface );

                // trivial bounds check:
                if ( node->getBound().contains(surface) )
                {
                    osg::Vec3d nvector;
                    point.createWorldUpVector(nvector);

                    osg::Vec3d start( surface + nvector*5e5 );
                    osg::Vec3d end  ( surface - nvector*5e5 );
                
                    // first time through, set up the intersector on demand
                    if ( !_patchLayersLSI.valid() )
                    {
                        _patchLayersLSI = new DPLineSegmentIntersector(start, end);
                        _patchLayersLSI->setIntersectionLimit( _patchLayersLSI->LIMIT_NEAREST );
                    }
                    else
                    {
                        _patchLayersLSI->reset();
                        _patchLayersLSI->setStart( start );
                        _patchLayersLSI->setEnd  ( end );
                    }

                    // try it.
                    iv.setIntersector( _patchLayersLSI.get() );
                    node->accept( iv );

                    // check for a result!!
                    if ( _patchLayersLSI->containsIntersections() )
                    {
                        osg::Vec3d isect = _patchLayersLSI->getIntersections().begin()->getWorldIntersectPoint();

                        // transform back to input SRS:
                        GeoPoint output;
                        output.fromWorld( point.getSRS(), isect );
                        out_elevation = output.z();
                        if ( out_actualResolution )
                            *out_actualResolution = 0.0;

                        return true;
                    }
                }
                else
                {
                    //OE_INFO << LC << "Trivial rejection (bounds check)" << std::endl;
                }
            }
        }
    }

    if ( _mapf.elevationLayers().empty() )
    {
        // this means there are no heightfields.
        out_elevation = 0.0;
        return true;        
    }

    // tile size (resolution of elevation tiles)
    unsigned tileSize = std::max(_mapf.getMapOptions().elevationTileSize().get(), 2u);

    //This is the max resolution that we actually have data at this point
    unsigned int bestAvailLevel = getMaxLevel( point.x(), point.y(), point.getSRS(), _mapf.getProfile());

    if (desiredResolution > 0.0)
    {
        unsigned int desiredLevel = _mapf.getProfile()->getLevelOfDetailForHorizResolution( desiredResolution, tileSize );
        if (desiredLevel < bestAvailLevel) bestAvailLevel = desiredLevel;
    }

    OE_DEBUG << LC << "Best available data level " << point.x() << ", " << point.y() << " = "  << bestAvailLevel << std::endl;

    // transform the input coords to map coords:
    GeoPoint mapPoint = point;
    if ( point.isValid() && !point.getSRS()->isHorizEquivalentTo( _mapf.getProfile()->getSRS() ) )
    {
        mapPoint = point.transform(_mapf.getProfile()->getSRS());
        if ( !mapPoint.isValid() )
        {
            OE_WARN << LC << "Fail: coord transform failed" << std::endl;
            return false;
        }
    }    

    // get the tilekey corresponding to the tile we need:
    TileKey key = _mapf.getProfile()->createTileKey( mapPoint.x(), mapPoint.y(), bestAvailLevel );
    if ( !key.valid() )
    {
        OE_WARN << LC << "Fail: coords fall outside map" << std::endl;
        return false;
    }
        
    bool result = false;      
    while (!result)
    {      
        GeoHeightField geoHF;
        TileCache::Record record;
        // Try to get the hf from the cache
        if ( _cache.get( key, record ) )
        {                        
            geoHF = record.value();
        }
        else
        {
            // Create it            
            osg::ref_ptr<osg::HeightField> hf = new osg::HeightField();
            hf->allocate( tileSize, tileSize );

            // Initialize the heightfield to nodata
            for (unsigned int i = 0; i < hf->getFloatArray()->size(); i++)
            {
                hf->getFloatArray()->at( i ) = NO_DATA_VALUE;
            }   

            if (_mapf.populateHeightField(hf, key, false))
            {                
                geoHF = GeoHeightField( hf.get(), key.getExtent() );
                _cache.insert( key, geoHF );
            }
        }

        if (geoHF.valid())
        {            
            float elevation = 0.0f;                 
            result = geoHF.getElevation( mapPoint.getSRS(), mapPoint.x(), mapPoint.y(), _mapf.getMapInfo().getElevationInterpolation(), mapPoint.getSRS(), elevation);                              
            if (result && elevation != NO_DATA_VALUE)
            {                        
                // see what the actual resolution of the heightfield is.
                if ( out_actualResolution )
                    *out_actualResolution = geoHF.getXInterval(); 
                out_elevation = (double)elevation;                
                break;
            }
            else
            {                               
                result = false;
            }
        }

        if (!result)
        {
            key = key.createParentKey();                        
            if (!key.valid())
            {
                break;
            }
        }         
    }

         

    osg::Timer_t end = osg::Timer::instance()->tick();
    _queries++;
    _totalTime += osg::Timer::instance()->delta_s( begin, end );

    return result;
}