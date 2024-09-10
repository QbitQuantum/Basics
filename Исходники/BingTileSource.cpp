    /**
     * Create and return an image for the given TileKey.
     */
    osg::Image* createImage( const TileKey& key, ProgressCallback* progress )
    {
        if (_debugDirect)
        {
            //osg::Image* image = new osg::Image;
            //image->allocateImage(256,256,1, GL_RGB, GL_UNSIGNED_BYTE);
            //return image;

            return osgDB::readImageFile( getDirectURI(key) );
            //return URI(getDirectURI(key)).getImage(_dbOptions.get(), progress);
        }

        // center point of the tile (will be in spherical mercator)
        double x, y;
        key.getExtent().getCentroid(x, y);

        // transform it to lat/long:
        GeoPoint geo;

        GeoPoint( getProfile()->getSRS(), x, y ).transform(
            getProfile()->getSRS()->getGeographicSRS(),
            geo );

        // contact the REST API. Docs are here:
        // http://msdn.microsoft.com/en-us/library/ff701716.aspx

        // construct the request URI:
        std::string request = Stringify()
            << std::setprecision(12)
            << _options.imageryMetadataAPI().get()     // base REST API
            << "/"    << _options.imagerySet().get()   // imagery set to use
            << "/"    << geo.y() << "," << geo.x()     // center point in lat/long
            << "?zl=" << key.getLOD() + 1              // zoom level
            << "&o=json"                               // response format
            << "&key=" << _options.key().get();        // API key

        // check the URI cache.
        URI                  location;
        TileURICache::Record rec;

        if ( _tileURICache.get(request, rec) )
        {
            location = URI(rec.value());
            //CacheStats stats = _tileURICache.getStats();
            //OE_INFO << "Ratio = " << (stats._hitRatio*100) << "%" << std::endl;
        }
        else
        {
            unsigned c = ++_apiCount;
            if ( c % 25 == 0 )
                OE_INFO << LC << "API calls = " << c << std::endl;
            
            // fetch it:
            ReadResult metadataResult = URI(request).readString(_dbOptions, progress);

            if ( metadataResult.failed() )
            {
                // check for a REST error:
                if ( metadataResult.code() == ReadResult::RESULT_SERVER_ERROR )
                {
                    OE_WARN << LC << "REST API request error!" << std::endl;

                    Config metadata;
                    std::string content = metadataResult.getString();
                    metadata.fromJSON( content );
                    ConfigSet errors = metadata.child("errorDetails").children();
                    for(ConfigSet::const_iterator i = errors.begin(); i != errors.end(); ++i )
                    {
                        OE_WARN << LC << "REST API: " << i->value() << std::endl;
                    }
                    return 0L;
                }
                else
                {
                    OE_WARN << LC << "Request error: " << metadataResult.getResultCodeString() << std::endl;
                }
                return 0L;
            }

            // decode it:
            Config metadata;
            if ( !metadata.fromJSON(metadataResult.getString()) )
            {
                OE_WARN << LC << "Error decoding REST API response" << std::endl;
                return 0L;
            }

            // check the vintage field. If it's empty, that means we got a "no data" tile.
            Config* vintageEnd = metadata.find("vintageEnd");
            if ( !vintageEnd || vintageEnd->value().empty() )
            {
                OE_DEBUG << LC << "NO data image encountered." << std::endl;
                return 0L;
            }

            // find the tile URI:
            Config* locationConf= metadata.find("imageUrl");
            if ( !locationConf )
            {
                OE_WARN << LC << "REST API JSON parsing error (imageUrl not found)" << std::endl;
                return 0L;
            }

            location = URI( locationConf->value() );
            _tileURICache.insert( request, location.full() );
        }

        // request the actual tile
        //OE_INFO << "key = " << key.str() << ", URL = " << location->value() << std::endl;

        //osg::Image* image = location.getImage(_dbOptions.get(), progress);
        osg::Image* image = osgDB::readImageFile( location.full() );

        if ( image &&  _geom.valid() )
        {
            GeometryRasterizer rasterizer( image->s(), image->t() );
            rasterizer.draw( _geom.get(), osg::Vec4(1,1,1,1) );
            osg::ref_ptr<osg::Image> overlay = rasterizer.finalize();
            ImageUtils::PixelVisitor<AlphaBlend> blend;
            blend.accept( overlay.get(), image );
        }

        return image;
    }