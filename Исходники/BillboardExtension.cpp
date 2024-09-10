bool
BillboardExtension::connect(MapNode* mapNode)
{
    if ( !mapNode )
    {
        OE_WARN << LC << "Illegal: MapNode cannot be null." << std::endl;
        return false;
    }

    OE_INFO << LC << "Connecting to MapNode.\n";

    if ( !_options.imageURI().isSet() )
    {
        OE_WARN << LC << "Illegal: image URI is required" << std::endl;
        return false;
    }

    if ( !_options.featureOptions().isSet() )
    {
        OE_WARN << LC << "Illegal: feature source is required" << std::endl;
        return false;
    }
    
    _features = FeatureSourceFactory::create( _options.featureOptions().value() );
    if ( !_features.valid() )
    {
        OE_WARN << LC << "Illegal: no valid feature source provided" << std::endl;
        return false;
    }

    //if ( _features->getGeometryType() != osgEarth::Symbology::Geometry::TYPE_POINTSET )
    //{
    //    OE_WARN << LC << "Illegal: only points currently supported" << std::endl;
    //    return false;
    //}

    _features->initialize( _dbOptions );

    osg::Vec3dArray* verts;
    if ( _features->getFeatureProfile() )
    {
        verts = new osg::Vec3dArray();
        
        OE_NOTICE << "Reading features...\n";
        osg::ref_ptr<FeatureCursor> cursor = _features->createFeatureCursor();
        while ( cursor.valid() && cursor->hasMore() )
        {
            Feature* f = cursor->nextFeature();
            if ( f && f->getGeometry() )
            {
                if ( f->getGeometry()->getComponentType() == Geometry::TYPE_POLYGON )
                {
                    FilterContext cx;
                    cx.setProfile( new FeatureProfile(_features->getFeatureProfile()->getExtent()) );

                    ScatterFilter scatter;
                    scatter.setDensity( _options.density().get() );
                    scatter.setRandom( true );
                    FeatureList featureList;
                    featureList.push_back(f);
                    scatter.push( featureList, cx );
                }

                // Init a filter to tranform feature in desired SRS 
                if (!mapNode->getMapSRS()->isEquivalentTo(_features->getFeatureProfile()->getSRS()))
                {
                    FilterContext cx;
                    cx.setProfile( new FeatureProfile(_features->getFeatureProfile()->getExtent()) );

                    TransformFilter xform( mapNode->getMapSRS() );
                    FeatureList featureList;
                    featureList.push_back(f);
                    cx = xform.push(featureList, cx);
                }

                GeometryIterator iter(f->getGeometry());
                while(iter.hasMore()) {
                    const Geometry* geom = iter.next();
                    osg::ref_ptr<osg::Vec3dArray> fVerts = geom->createVec3dArray();
                    verts->insert(verts->end(), fVerts->begin(), fVerts->end());
                }
            }
        }
    }
    else
    {
        OE_WARN << LC << "Illegal: feature source has no SRS" << std::endl;
        return false;
    }


    if ( verts && verts->size() > 0 )
    {
        OE_NOTICE << LC << "Read " << verts->size() << " points.\n";

        //localize all the verts
        GeoPoint centroid;
        _features->getFeatureProfile()->getExtent().getCentroid(centroid);
        centroid = centroid.transform(mapNode->getMapSRS());

        OE_NOTICE << "Centroid = " << centroid.x() << ", " << centroid.y() << "\n";

        osg::Matrixd l2w, w2l;
        centroid.createLocalToWorld(l2w);
        w2l.invert(l2w);

        osg::MatrixTransform* mt = new osg::MatrixTransform;
        mt->setMatrix(l2w);

        OE_NOTICE << "Clamping elevations...\n";
        osgEarth::ElevationQuery eq(mapNode->getMap());
        eq.setFallBackOnNoData( true );
        eq.getElevations(verts->asVector(), mapNode->getMapSRS(), true, 0.005);
        
        OE_NOTICE << "Building geometry...\n";
        osg::Vec3Array* normals = new osg::Vec3Array(verts->size());

        osg::Vec4Array* colors = new osg::Vec4Array(verts->size());
        Random rng;

        for (int i=0; i < verts->size(); i++)
        {
            GeoPoint vert(mapNode->getMapSRS(), (*verts)[i], osgEarth::ALTMODE_ABSOLUTE);

            osg::Vec3d world;
            vert.toWorld(world);
            (*verts)[i] = world * w2l;

            osg::Vec3 normal = world;
            normal.normalize();
            (*normals)[i] = osg::Matrix::transform3x3(normal, w2l);

            double n = rng.next();
            (*colors)[i].set( n, n, n, 1 );
        }

        //create geom and primitive sets
        osg::Geometry* geometry = new osg::Geometry();
        geometry->setVertexArray( verts );
        geometry->setNormalArray( normals );
        geometry->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
        geometry->setColorArray(colors);
        geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );

        geometry->addPrimitiveSet( new osg::DrawArrays( GL_POINTS, 0, verts->size() ) );

        //create image and texture to render to
        osg::Texture2D* tex = new osg::Texture2D(_options.imageURI()->getImage(_dbOptions));
        tex->setResizeNonPowerOfTwoHint(false);
        tex->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR );
        tex->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );
        tex->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        tex->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

        geometry->setName("BillboardPoints");

        osg::Geode* geode = new osg::Geode;
        geode->addDrawable(geometry);

        //osg::ref_ptr<StateSetCache> cache = new StateSetCache();
        //Registry::shaderGenerator().run(geode, cache.get());

        //set the texture related uniforms
        osg::StateSet* geode_ss = geode->getOrCreateStateSet();
        geode_ss->setTextureAttributeAndModes( 2, tex, 1 );
        geode_ss->getOrCreateUniform("billboard_tex", osg::Uniform::SAMPLER_2D)->set( 2 );

        float bbWidth = (float)tex->getImage()->s() / 2.0f;
        float bbHeight = (float)tex->getImage()->t();
        float aspect = (float)tex->getImage()->s() / (float)tex->getImage()->t();
        if (_options.height().isSet())
        {
            bbHeight = _options.height().get();
            if (!_options.width().isSet())
            {
                bbWidth = bbHeight * aspect / 2.0f;
            }
        }
        if (_options.width().isSet())
        {
            bbWidth = _options.width().get() / 2.0f;
            if (!_options.height().isSet())
            {
                bbHeight = _options.width().get() / aspect;
            }
        }

        geode_ss->getOrCreateUniform("billboard_width", osg::Uniform::FLOAT)->set( bbWidth );
        geode_ss->getOrCreateUniform("billboard_height", osg::Uniform::FLOAT)->set( bbHeight );
        geode_ss->setMode(GL_BLEND, osg::StateAttribute::ON);

        //for now just using an osg::Program
        //TODO: need to add GeometryShader support to the shader comp setup
        VirtualProgram* vp = VirtualProgram::getOrCreate(geode_ss);
        vp->setName( "osgEarth Billboard Extension" );

        ShaderPackage shaders;
        shaders.add( "Billboard geometry shader", billboardGeomShader );
        shaders.add( "Billboard fragment shader", billboardFragShader );
        shaders.loadAll( vp );

        geode_ss->setMode( GL_CULL_FACE, osg::StateAttribute::OFF );
        geode->setCullingActive(false);

        mt->addChild(geode);
        mapNode->getModelLayerGroup()->addChild(mt);

        return true;
    }

    return false;
}