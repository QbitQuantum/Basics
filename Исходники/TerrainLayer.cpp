const Status&
TerrainLayer::open()
{
    if ( !_openCalled )
    {
        // Call base class
        if (VisibleLayer::open().isError())
            return getStatus();

        // Create an L2 mem cache that sits atop the main cache, if necessary.
        // For now: use the same L2 cache size at the driver.
        int l2CacheSize = options().driver()->L2CacheSize().get();
    
        // See if it was overridden with an env var.
        char const* l2env = ::getenv( "OSGEARTH_L2_CACHE_SIZE" );
        if ( l2env )
        {
            l2CacheSize = as<int>( std::string(l2env), 0 );
            OE_INFO << LC << "L2 cache size set from environment = " << l2CacheSize << "\n";
        }

        // Env cache-only mode also disables the L2 cache.
        char const* noCacheEnv = ::getenv( "OSGEARTH_MEMORY_PROFILE" );
        if ( noCacheEnv )
        {
            l2CacheSize = 0;
        }

        // Initialize the l2 cache if it's size is > 0
        if ( l2CacheSize > 0 )
        {
            _memCache = new MemCache( l2CacheSize );
        }

        // create the unique cache ID for the cache bin.
        //std::string cacheId;

        if (options().cacheId().isSet() && !options().cacheId()->empty())
        {
            // user expliticy set a cacheId in the terrain layer options.
            // this appears to be a NOP; review for removal -gw
            _runtimeCacheId = options().cacheId().get();
        }
        else
        {
            // system will generate a cacheId from the layer configuration.
            Config hashConf = options().getConfig();

            // remove non-data properties.
            hashConf.remove("name");
            hashConf.remove("enabled");
            hashConf.remove("cacheid");
            hashConf.remove("cache_only");
            hashConf.remove("cache_enabled");
            hashConf.remove("cache_policy");
            hashConf.remove("visible");
            hashConf.remove("l2_cache_size");

            OE_DEBUG << "hashConfFinal = " << hashConf.toJSON(true) << std::endl;

            unsigned hash = osgEarth::hashString(hashConf.toJSON());
            _runtimeCacheId = Stringify() << std::hex << std::setw(8) << std::setfill('0') << hash;
        }

        // Now that we know the cache ID, establish the cache settings for this Layer.
        // Start by cloning whatever CacheSettings were inherited in the read options
        // (typically from the Map).
        CacheSettings* oldSettings = CacheSettings::get(_readOptions.get());
        _cacheSettings = oldSettings ? new CacheSettings(*oldSettings) : new CacheSettings();

        // Integrate a cache policy from this Layer's options:
        _cacheSettings->integrateCachePolicy(options().cachePolicy());

        // If you created the layer with a pre-created tile source, it will already by set.
        if (!_tileSource.valid())
        {
            osg::ref_ptr<TileSource> ts;

            // as long as we're not in cache-only mode, try to create the TileSource.
            if (_cacheSettings->cachePolicy()->isCacheOnly())
            {
                OE_INFO << LC << "Opening in cache-only mode\n";
            }
            else if (isTileSourceExpected())
            {
                // Initialize the tile source once and only once.
                ts = createAndOpenTileSource();
            }

            // If we loaded a tile source, give it some information about caching
            // if appropriate.
            if (ts.valid())
            {
                if (_cacheSettings->isCacheEnabled())
                {
                    // read the cache policy hint from the tile source unless user expressly set 
                    // a policy in the initialization options. In other words, the hint takes
                    // ultimate priority (even over the Registry override) unless expressly
                    // overridden in the layer options!
                    refreshTileSourceCachePolicyHint( ts.get() );

                    // Unless the user has already configured an expiration policy, use the "last modified"
                    // timestamp of the TileSource to set a minimum valid cache entry timestamp.
                    const CachePolicy& cp = options().cachePolicy().get();

                    if ( !cp.minTime().isSet() && !cp.maxAge().isSet() && ts->getLastModifiedTime() > 0)
                    {
                        // The "effective" policy overrides the runtime policy, but it does not get serialized.
                        _cacheSettings->cachePolicy()->mergeAndOverride( cp );
                        _cacheSettings->cachePolicy()->minTime() = ts->getLastModifiedTime();
                        OE_INFO << LC << "driver says min valid timestamp = " << DateTime(*cp.minTime()).asRFC1123() << "\n";
                    }
                }

                // All is well - set the tile source.
                if ( !_tileSource.valid() )
                {
                    _tileSource = ts.release();
                }
            }
        }
        else
        {
            // User supplied the tile source, so attempt to get its profile:
            setProfile(_tileSource->getProfile() );
            if (!_profile.valid())
            {
                setStatus( Status::Error(getName(), "Cannot establish profile") );
            }
        }

        // Finally, open and activate a caching bin for this layer.
        if (_cacheSettings->isCacheEnabled())
        {
            CacheBin* bin = _cacheSettings->getCache()->addBin(_runtimeCacheId);
            if (bin)
            {
                _cacheSettings->setCacheBin(bin);
                OE_INFO << LC << "Cache bin is [" << bin->getID() << "]\n";
            }
        }

        // Store the updated settings in the read options so we can propagate 
        // them as necessary.
        _cacheSettings->store(_readOptions.get());
        OE_INFO << LC << _cacheSettings->toString() << "\n";

        // Done!
        _openCalled = true;
                        
    }

    return getStatus();
}