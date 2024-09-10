    /** override */
    Status initialize( const osgDB::Options* dbOptions )
    {
        osg::ref_ptr<const Profile> result;

        char sep = _options.url()->full().find_first_of('?') == std::string::npos? '?' : '&';

        URI capUrl = _options.capabilitiesUrl().value();
        if ( capUrl.empty() )
        {
            capUrl = URI(
                _options.url()->full() + 
                sep + 
                std::string("SERVICE=WMS") +
                std::string("&VERSION=") + _options.wmsVersion().value() +
                std::string("&REQUEST=GetCapabilities") );
        }

        //Try to read the WMS capabilities
        osg::ref_ptr<WMSCapabilities> capabilities = WMSCapabilitiesReader::read( capUrl, dbOptions );
        if ( !capabilities.valid() )
        {
            return Status::Error( Status::ResourceUnavailable, "Unable to read WMS GetCapabilities." );
        }
        else
        {
            OE_INFO << LC << "Got capabilities from " << capUrl.full() << std::endl;
        }

        if ( _formatToUse.empty() && capabilities.valid() )
        {
            _formatToUse = capabilities->suggestExtension();
            OE_INFO << LC << "No format specified, capabilities suggested extension " << _formatToUse << std::endl;
        }

        if ( _formatToUse.empty() )
            _formatToUse = "png";
       
        if ( _srsToUse.empty() )
            _srsToUse = "EPSG:4326";

        std::string wmsFormatToUse = _options.wmsFormat().value();

        //Initialize the WMS request prototype
        std::stringstream buf;

        // first the mandatory keys:
        buf
            << std::fixed << _options.url()->full() << sep
	    << "SERVICE=WMS"
            << "&VERSION=" << _options.wmsVersion().value()
            << "&REQUEST=GetMap"
            << "&LAYERS=" << _options.layers().value()
            << "&FORMAT=" << ( wmsFormatToUse.empty() ? std::string("image/") + _formatToUse : wmsFormatToUse )
            << "&STYLES=" << _options.style().value()
            << (_options.wmsVersion().value() == "1.3.0" ? "&CRS=" : "&SRS=") << _srsToUse            
            << "&WIDTH="<< getPixelsPerTile()
            << "&HEIGHT=" << getPixelsPerTile()
            << "&BBOX=%lf,%lf,%lf,%lf";

        // then the optional keys:
        if ( _options.transparent().isSet() )
            buf << "&TRANSPARENT=" << (_options.transparent() == true ? "TRUE" : "FALSE");
            

        _prototype = "";
        _prototype = buf.str();

        //OE_NOTICE << "Prototype " << _prototype << std::endl;

        osg::ref_ptr<SpatialReference> wms_srs = SpatialReference::create( _srsToUse );

        // check for spherical mercator:
        if ( wms_srs.valid() && wms_srs->isEquivalentTo( osgEarth::Registry::instance()->getSphericalMercatorProfile()->getSRS() ) )
        {
            result = osgEarth::Registry::instance()->getSphericalMercatorProfile();
        }
        else if (wms_srs.valid() && wms_srs->isEquivalentTo( osgEarth::Registry::instance()->getGlobalGeodeticProfile()->getSRS()))
        {
            result = osgEarth::Registry::instance()->getGlobalGeodeticProfile();
        }

        // Next, try to glean the extents from the layer list
        if ( capabilities.valid() )
        {
            StringTokenizer tok(",");
            StringVector tized;
            tok.tokenize(_options.layers().value(), tized);

            for (StringVector::const_iterator itr = tized.begin(); itr != tized.end(); ++itr)
            {
                std::string layerName = *itr;
                WMSLayer* layer = capabilities->getLayerByName(layerName);
                if (layer)
                {
                    // Get the lat/lon extents
                    double minLon, minLat, maxLon, maxLat;
                    layer->getLatLonExtents(minLon, minLat, maxLon, maxLat);
                    GeoExtent wgs84Extent(SpatialReference::create("wgs84"), minLon, minLat, maxLon, maxLat);
                    getDataExtents().push_back(DataExtent(wgs84Extent, 0));
                }
            }

            // If we don't have a profile yet, transform the lat/lon extents to the requested srs and use it as the extents of the profile.
            if (!result.valid())
            {
                const SpatialReference* srs = SpatialReference::create(_srsToUse);
                GeoExtent totalExtent(srs);
                for (DataExtentList::const_iterator itr = getDataExtents().begin(); itr != getDataExtents().end(); ++itr)
                {
                    GeoExtent dataExtent = *itr;
                    GeoExtent nativeExtent;
                    dataExtent.transform(srs, nativeExtent);
                    totalExtent.expandToInclude(nativeExtent);
                }
                result = Profile::create(srs, totalExtent.xMin(), totalExtent.yMin(), totalExtent.xMax(), totalExtent.yMax());
            }
        }

        // Last resort: create a global extent profile (only valid for global maps)
        if ( !result.valid() && wms_srs->isGeographic())
        {
            result = osgEarth::Registry::instance()->getGlobalGeodeticProfile();
        }    

#ifdef SUPPORT_JPL_TILESERVICE
        // JPL uses an experimental interface called TileService -- ping to see if that's what
        // we are trying to read:
        URI tsUrl = _options.tileServiceUrl().value();
        if ( tsUrl.empty() )
        {
            tsUrl = URI(_options.url()->full() + sep + std::string("request=GetTileService"), tsUrl.context());
        }

        OE_INFO << LC << "Testing for JPL/TileService at " << tsUrl.full() << std::endl;
        osg::ref_ptr<TileService> tileService = TileServiceReader::read(tsUrl.full(), dbOptions);
        if (tileService.valid())
        {
            OE_INFO << LC << "Found JPL/TileService spec" << std::endl;
            TileService::TilePatternList patterns;
            tileService->getMatchingPatterns(
                _options.layers().value(),
                _formatToUse,
                _options.style().value(),
                _srsToUse,
                getPixelsPerTile(),
                getPixelsPerTile(),
                patterns );

            if (patterns.size() > 0)
            {
                result = tileService->createProfile( patterns );
                _prototype = _options.url()->full() + sep + patterns[0].getPrototype();
            }
        }
        else
        {
            OE_INFO << LC << "No JPL/TileService spec found; assuming standard WMS" << std::endl;
        }
#endif

        // Use the override profile if one is passed in.
        if ( getProfile() == 0L )
        {
            setProfile( result.get() );
        }

        if ( getProfile() )
        {
            OE_INFO << LC << "Profile=" << getProfile()->toString() << std::endl;

            // set up the cache options properly for a TileSource.
            _dbOptions = Registry::instance()->cloneOrCreateOptions( dbOptions );            

            return Status::OK();
        }
        else
        {
            return Status::Error( "Unable to establish profile" );
        }
    }