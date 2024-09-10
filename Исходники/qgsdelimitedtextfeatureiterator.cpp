QgsDelimitedTextFeatureIterator::QgsDelimitedTextFeatureIterator( QgsDelimitedTextFeatureSource* source, bool ownSource, const QgsFeatureRequest& request )
    : QgsAbstractFeatureIteratorFromSource<QgsDelimitedTextFeatureSource>( source, ownSource, request )
    , mTestGeometryExact( false )
{

  // Determine mode to use based on request...
  QgsDebugMsg( "Setting up QgsDelimitedTextIterator" );

  // Does the layer have geometry - will revise later to determine if we actually need to
  // load it.
  bool hasGeometry = mSource->mGeomRep != QgsDelimitedTextProvider::GeomNone;

  // Does the layer have an explicit or implicit subset (implicit subset is if we have geometry which can
  // be invalid)

  mTestSubset = mSource->mSubsetExpression;
  mTestGeometry = false;

  mMode = FileScan;
  if ( request.filterType() == QgsFeatureRequest::FilterFid )
  {
    QgsDebugMsg( "Configuring for returning single id" );
    mFeatureIds.append( request.filterFid() );
    mMode = FeatureIds;
    mTestSubset = false;
  }
  // If have geometry and testing geometry then evaluate options...
  // If we don't have geometry then all records pass geometry filter.
  // CC: 2013-05-09
  // Not sure about intended relationship between filtering on geometry and
  // requesting no geometry? Have preserved current logic of ignoring spatial filter
  // if not requesting geometry.

  else if ( request.filterType() == QgsFeatureRequest::FilterRect && hasGeometry )
  {
    QgsDebugMsg( "Configuring for rectangle select" );
    mTestGeometry = true;
    // Exact intersection test only applies for WKT geometries
    mTestGeometryExact = mRequest.flags() & QgsFeatureRequest::ExactIntersect
                         && mSource->mGeomRep == QgsDelimitedTextProvider::GeomAsWkt;

    QgsRectangle rect = request.filterRect();

    // If request doesn't overlap extents, then nothing to return
    if ( ! rect.intersects( mSource->mExtent ) )
    {
      QgsDebugMsg( "Rectangle outside layer extents - no features to return" );
      mMode = FeatureIds;
    }
    // If the request extents include the entire layer, then revert to
    // a file scan

    else if ( rect.contains( mSource->mExtent ) )
    {
      QgsDebugMsg( "Rectangle contains layer extents - bypass spatial filter" );
      mTestGeometry = false;
    }
    // If we have a spatial index then use it.  The spatial index already accounts
    // for the subset.  Also means we don't have to test geometries unless doing exact
    // intersection

    else if ( mSource->mUseSpatialIndex )
    {
      mFeatureIds = mSource->mSpatialIndex->intersects( rect );
      // Sort for efficient sequential retrieval
      qSort( mFeatureIds.begin(), mFeatureIds.end() );
      QgsDebugMsg( QString( "Layer has spatial index - selected %1 features from index" ).arg( mFeatureIds.size() ) );
      mMode = FeatureIds;
      mTestSubset = false;
      mTestGeometry = mTestGeometryExact;
    }
  }

  // If we have a subset index then use it..
  if ( mMode == FileScan && mSource->mUseSubsetIndex )
  {
    QgsDebugMsg( QString( "Layer has subset index - use %1 items from subset index" ).arg( mSource->mSubsetIndex.size() ) );
    mTestSubset = false;
    mMode = SubsetIndex;
  }

  // Otherwise just have to scan the file
  if ( mMode == FileScan )
  {
    QgsDebugMsg( "File will be scanned for desired features" );
  }

  // If the layer has geometry, do we really need to load it?
  // We need it if it is asked for explicitly in the request,
  // if we are testing geometry (ie spatial filter), or
  // if testing the subset expression.
  if ( hasGeometry
       && (
         !( mRequest.flags() & QgsFeatureRequest::NoGeometry )
         || mTestGeometry
         || ( mTestSubset && mSource->mSubsetExpression->needsGeometry() )
       )
     )
  {
    mLoadGeometry = true;
  }
  else
  {
    QgsDebugMsgLevel( "Feature geometries not required", 4 );
    mLoadGeometry = false;
  }

  QgsDebugMsg( QString( "Iterator is scanning file: " ) + ( mMode == FileScan ? "Yes" : "No" ) );
  QgsDebugMsg( QString( "Iterator is loading geometries: " ) + ( mLoadGeometry ? "Yes" : "No" ) );
  QgsDebugMsg( QString( "Iterator is testing geometries: " ) + ( mTestGeometry ? "Yes" : "No" ) );
  QgsDebugMsg( QString( "Iterator is testing subset: " ) + ( mTestSubset ? "Yes" : "No" ) );

  rewind();
}