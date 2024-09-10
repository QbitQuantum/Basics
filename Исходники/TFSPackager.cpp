void
    TFSPackager::package( FeatureSource* features, const std::string& destination, const std::string& layername, const std::string& description )
{   
    if (!_destSRSString.empty())
    {
        _srs = SpatialReference::create( _destSRSString );
    }

    //Get the destination SRS from the feature source if it's not already set
    if (!_srs.valid())
    {
        _srs = features->getFeatureProfile()->getSRS();
    }
	
    //Get the extent of the dataset, or use the custom extent value
    GeoExtent srsExtent = _customExtent;
    if (!srsExtent.isValid())
        srsExtent = features->getFeatureProfile()->getExtent();

    //Transform to lat/lon extents
    GeoExtent extent = srsExtent.transform( _srs.get() );

    osg::ref_ptr< const osgEarth::Profile > profile = osgEarth::Profile::create(extent.getSRS(), extent.xMin(), extent.yMin(), extent.xMax(), extent.yMax(), 1, 1);


    TileKey rootKey = TileKey(0, 0, 0, profile );    


    osg::ref_ptr< FeatureTile > root = new FeatureTile( rootKey );
    //Loop through all the features and try to insert them into the quadtree
    osg::ref_ptr< FeatureCursor > cursor = features->createFeatureCursor( _query );
    int added = 0;
    int failed = 0;
    int skipped = 0;
    int highestLevel = 0;

    while (cursor.valid() && cursor->hasMore())
    {        
        osg::ref_ptr< Feature > feature = cursor->nextFeature();

        //Reproject the feature to the dest SRS if it's not already
        if (!feature->getSRS()->isEquivalentTo( _srs ) )
        {
            feature->transform( _srs );
        }

        if (feature->getGeometry() && feature->getGeometry()->getBounds().valid() && feature->getGeometry()->isValid())
        {

            AddFeatureVisitor v(feature.get(), _maxFeatures, _firstLevel, _maxLevel, _method);
            root->accept( &v );
            if (!v._added)
            {
                OE_NOTICE << "Failed to add feature " << feature->getFID() << std::endl;
                failed++;
            }
            else
            {                
                if (highestLevel < v._levelAdded)
                {
                    highestLevel = v._levelAdded;
                }
                added++;
                OE_DEBUG << "Added " << added << std::endl;
            }   
        }
        else
        {
            OE_NOTICE << "Skipping feature " << feature->getFID() << " with null or invalid geometry" << std::endl;
            skipped++;
        }
    }   
    OE_NOTICE << "Added=" << added << " Skipped=" << skipped << " Failed=" << failed << std::endl;

#if 1
    // Print the width of tiles at each level
    for (int i = 0; i <= highestLevel; ++i)
    {
        TileKey tileKey(i, 0, 0, profile);
        GeoExtent tileExtent = tileKey.getExtent();
        OE_NOTICE << "Level " << i << " tile size: " << tileExtent.width() << std::endl;
    }
#endif

    WriteFeaturesVisitor write(features, destination, _method, _srs);
    root->accept( &write );

    //Write out the meta doc
    TFSLayer layer;
    layer.setTitle( layername );
    layer.setAbstract( description );
    layer.setFirstLevel( _firstLevel );
    layer.setMaxLevel( highestLevel );
    layer.setExtent( profile->getExtent() );
    layer.setSRS( _srs.get() );
    TFSReaderWriter::write( layer, osgDB::concatPaths( destination, "tfs.xml"));

}