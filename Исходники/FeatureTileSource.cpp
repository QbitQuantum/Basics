bool
FeatureTileSource::queryAndRenderFeaturesForStyle(const Style&     style,
                                                  const Query&     query,
                                                  osg::Referenced* data,
                                                  const GeoExtent& imageExtent,
                                                  osg::Image*      out_image)
{   
    // first we need the overall extent of the layer:
    const GeoExtent& featuresExtent = getFeatureSource()->getFeatureProfile()->getExtent();
    
    // convert them both to WGS84, intersect the extents, and convert back.
    GeoExtent featuresExtentWGS84 = featuresExtent.transform( featuresExtent.getSRS()->getGeographicSRS() );
    GeoExtent imageExtentWGS84 = imageExtent.transform( featuresExtent.getSRS()->getGeographicSRS() );
    GeoExtent queryExtentWGS84 = featuresExtentWGS84.intersectionSameSRS( imageExtentWGS84 );
    if ( queryExtentWGS84.isValid() )
    {
        GeoExtent queryExtent = queryExtentWGS84.transform( featuresExtent.getSRS() );

        // incorporate the image extent into the feature query for this style:
        Query localQuery = query;
        localQuery.bounds() = 
            query.bounds().isSet() ? query.bounds()->unionWith( queryExtent.bounds() ) :
            queryExtent.bounds();

        // query the feature source:
        osg::ref_ptr<FeatureCursor> cursor = _features->createFeatureCursor( localQuery );

        // now copy the resulting feature set into a list, converting the data
        // types along the way if a geometry override is in place:
        FeatureList cellFeatures;
        while( cursor.valid() && cursor->hasMore() )
        {
            Feature* feature = cursor->nextFeature();
            Geometry* geom = feature->getGeometry();
            if ( geom )
            {
                // apply a type override if requested:
                if (_options.geometryTypeOverride().isSet() &&
                    _options.geometryTypeOverride() != geom->getComponentType() )
                {
                    geom = geom->cloneAs( _options.geometryTypeOverride().value() );
                    if ( geom )
                        feature->setGeometry( geom );
                }
            }
            if ( geom )
            {
                cellFeatures.push_back( feature );
            }
        }

        //OE_NOTICE
        //    << "Rendering "
        //    << cellFeatures.size()
        //    << " features in ("
        //    << queryExtent.toString() << ")"
        //    << std::endl;

        return renderFeaturesForStyle( style, cellFeatures, data, imageExtent, out_image );
    }
    else
    {
        return false;
    }
}