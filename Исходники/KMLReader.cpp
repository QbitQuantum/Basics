osg::Node*
KMLReader::read( const Config& conf, const osgDB::Options* dbOptions )
{
    osg::Group* root = new osg::Group();
    root->ref();

    root->setName( conf.referrer() );

    KMLContext cx;
    cx._mapNode   = _mapNode;
    cx._sheet     = new StyleSheet();
    cx._options   = _options;
    cx._srs       = SpatialReference::create( "wgs84", "egm96" );
    cx._groupStack.push( root );

    // clone the dbOptions, and install a resource cache if there isn't one already:
    URIResultCache defaultUriCache;
    if ( !URIResultCache::from(dbOptions) )
    {
        osgDB::Options* newOptions = Registry::instance()->cloneOrCreateOptions();
        defaultUriCache.apply( newOptions );
        cx._dbOptions = newOptions;
    }
    else
    {
        cx._dbOptions = dbOptions;
    }

    // intialize the KML options with the defaults if necessary:
    KMLOptions blankOptions;
    if ( cx._options == 0L )
        cx._options = &blankOptions;

    if ( cx._options->iconAndLabelGroup().valid() && cx._options->declutter() == true )
    {
        Decluttering::setEnabled( cx._options->iconAndLabelGroup()->getOrCreateStateSet(), true );
    }

    const Config* top = conf.hasChild("kml" ) ? conf.child_ptr("kml") : &conf;

    if ( top && !top->empty() )
    {
        KML_Root kmlRoot;
        kmlRoot.scan ( *top, cx );    // first pass
        kmlRoot.scan2( *top, cx );   // second pass
        kmlRoot.build( *top, cx );   // third pass.
    }

    URIResultCache* cacheUsed = URIResultCache::from(cx._dbOptions.get());
    CacheStats stats = cacheUsed->getStats();
    OE_INFO << LC << "URI Cache: " << stats._queries << " reads, " << (stats._hitRatio*100.0) << "% hits" << std::endl;

    return root;
}