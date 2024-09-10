 /**
  * Gets all the features that intersect the extent
  */
 void getFeatures(const GeoExtent& extent, FeatureList& features)
 {
     GeoExtent localExtent = extent.transform( _featureSource->getFeatureProfile()->getSRS() );
     Query query;
     query.bounds() = localExtent.bounds();
     if (localExtent.intersects( _featureSource->getFeatureProfile()->getExtent()))
     {
         osg::ref_ptr< FeatureCursor > cursor = _featureSource->createFeatureCursor( query );
         if (cursor)
         {
             cursor->fill( features );
         }
     }     
 }