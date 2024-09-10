bool QgsGPXProvider::nextFeature( QgsFeature& feature )
{
  feature.setValid( false );
  bool result = false;

  QgsAttributeList::const_iterator iter;

  if ( mFeatureType == WaypointType )
  {
    // go through the list of waypoints and return the first one that is in
    // the bounds rectangle
    for ( ; mWptIter != data->waypointsEnd(); ++mWptIter )
    {
      const QgsWaypoint* wpt;
      wpt = &( *mWptIter );
      if ( boundsCheck( wpt->lon, wpt->lat ) )
      {
        feature.setFeatureId( wpt->id );
        result = true;

        // some wkb voodoo
        if ( mFetchGeom )
        {
          char* geo = new char[21];
          std::memset( geo, 0, 21 );
          geo[0] = QgsApplication::endian();
          geo[geo[0] == QgsApplication::NDR ? 1 : 4] = QGis::WKBPoint;
          std::memcpy( geo + 5, &wpt->lon, sizeof( double ) );
          std::memcpy( geo + 13, &wpt->lat, sizeof( double ) );
          feature.setGeometryAndOwnership(( unsigned char * )geo, sizeof( wkbPoint ) );
        }
        feature.setValid( true );

        // add attributes if they are wanted
        for ( iter = mAttributesToFetch.begin(); iter != mAttributesToFetch.end(); ++iter )
        {
          switch ( *iter )
          {
            case NameAttr:
              feature.addAttribute( NameAttr, QVariant( wpt->name ) );
              break;
            case EleAttr:
              if ( wpt->ele != -std::numeric_limits<double>::max() )
                feature.addAttribute( EleAttr, QVariant( wpt->ele ) );
              break;
            case SymAttr:
              feature.addAttribute( SymAttr, QVariant( wpt->sym ) );
              break;
            case CmtAttr:
              feature.addAttribute( CmtAttr, QVariant( wpt->cmt ) );
              break;
            case DscAttr:
              feature.addAttribute( DscAttr, QVariant( wpt->desc ) );
              break;
            case SrcAttr:
              feature.addAttribute( SrcAttr, QVariant( wpt->src ) );
              break;
            case URLAttr:
              feature.addAttribute( URLAttr, QVariant( wpt->url ) );
              break;
            case URLNameAttr:
              feature.addAttribute( URLNameAttr, QVariant( wpt->urlname ) );
              break;
          }
        }

        ++mWptIter;
        break;
      }
    }
  }

  else if ( mFeatureType == RouteType )
  {
    // go through the routes and return the first one that is in the bounds
    // rectangle
    for ( ; mRteIter != data->routesEnd(); ++mRteIter )
    {
      const QgsRoute* rte;
      rte = &( *mRteIter );

      if ( rte->points.size() == 0 )
        continue;
      const QgsRectangle& b( *mSelectionRectangle );
      if (( rte->xMax >= b.xMinimum() ) && ( rte->xMin <= b.xMaximum() ) &&
          ( rte->yMax >= b.yMinimum() ) && ( rte->yMin <= b.yMaximum() ) )
      {
        // some wkb voodoo
        int nPoints = rte->points.size();
        char* geo = new char[9 + 16 * nPoints];
        std::memset( geo, 0, 9 + 16 * nPoints );
        geo[0] = QgsApplication::endian();
        geo[geo[0] == QgsApplication::NDR ? 1 : 4] = QGis::WKBLineString;
        std::memcpy( geo + 5, &nPoints, 4 );
        for ( uint i = 0; i < rte->points.size(); ++i )
        {
          std::memcpy( geo + 9 + 16 * i, &rte->points[i].lon, sizeof( double ) );
          std::memcpy( geo + 9 + 16 * i + 8, &rte->points[i].lat, sizeof( double ) );
        }

        //create QgsGeometry and use it for intersection test
        //if geometry is to be fetched, it is attached to the feature, otherwise we delete it
        QgsGeometry* theGeometry = new QgsGeometry();
        theGeometry->fromWkb(( unsigned char * )geo, 9 + 16 * nPoints );
        bool intersection = theGeometry->intersects( b );//use geos for precise intersection test

        if ( !intersection )
        {
          delete theGeometry;
        }
        else
        {
          if ( mFetchGeom )
          {
            feature.setGeometry( theGeometry );
          }
          else
          {
            delete theGeometry;
          }
          feature.setFeatureId( rte->id );
          result = true;
          feature.setValid( true );

          // add attributes if they are wanted
          for ( iter = mAttributesToFetch.begin(); iter != mAttributesToFetch.end(); ++iter )
          {
            switch ( *iter )
            {
              case NameAttr:
                feature.addAttribute( NameAttr, QVariant( rte->name ) );
                break;
              case NumAttr:
                if ( rte->number != std::numeric_limits<int>::max() )
                  feature.addAttribute( NumAttr, QVariant( rte->number ) );
                break;
              case CmtAttr:
                feature.addAttribute( CmtAttr, QVariant( rte->cmt ) );
                break;
              case DscAttr:
                feature.addAttribute( DscAttr, QVariant( rte->desc ) );
                break;
              case SrcAttr:
                feature.addAttribute( SrcAttr, QVariant( rte->src ) );
                break;
              case URLAttr:
                feature.addAttribute( URLAttr, QVariant( rte->url ) );
                break;
              case URLNameAttr:
                feature.addAttribute( URLNameAttr, QVariant( rte->urlname ) );
                break;
            }
          }

          ++mRteIter;
          break;

        }

        //++mRteIter;
        //xbreak;
      }
    }
  }

  else if ( mFeatureType == TrackType )
  {
    // go through the tracks and return the first one that is in the bounds
    // rectangle
    for ( ; mTrkIter != data->tracksEnd(); ++mTrkIter )
    {
      const QgsTrack* trk;
      trk = &( *mTrkIter );

      QgsDebugMsg( QString( "GPX feature track segments: %1" ).arg( trk->segments.size() ) );
      if ( trk->segments.size() == 0 )
        continue;

      // A track consists of several segments. Add all those segments into one.
      int totalPoints = 0;;
      for ( std::vector<QgsTrackSegment>::size_type i = 0; i < trk->segments.size(); i ++ )
      {
        totalPoints += trk->segments[i].points.size();
      }
      if ( totalPoints == 0 )
        continue;
      QgsDebugMsg( "GPX feature track total points: " + QString::number( totalPoints ) );
      const QgsRectangle& b( *mSelectionRectangle );
      if (( trk->xMax >= b.xMinimum() ) && ( trk->xMin <= b.xMaximum() ) &&
          ( trk->yMax >= b.yMinimum() ) && ( trk->yMin <= b.yMaximum() ) )
      {
        // some wkb voodoo
        char* geo = new char[9 + 16 * totalPoints];
        if ( !geo )
        {
          QgsDebugMsg( "Too large track!!!" );
          return false;
        }
        std::memset( geo, 0, 9 + 16 * totalPoints );
        geo[0] = QgsApplication::endian();
        geo[geo[0] == QgsApplication::NDR ? 1 : 4] = QGis::WKBLineString;
        std::memcpy( geo + 5, &totalPoints, 4 );

        int thisPoint = 0;
        for ( std::vector<QgsTrackSegment>::size_type k = 0; k < trk->segments.size(); k++ )
        {
          int nPoints = trk->segments[k].points.size();
          for ( int i = 0; i < nPoints; ++i )
          {
            std::memcpy( geo + 9 + 16 * thisPoint,     &trk->segments[k].points[i].lon, sizeof( double ) );
            std::memcpy( geo + 9 + 16 * thisPoint + 8, &trk->segments[k].points[i].lat, sizeof( double ) );
            thisPoint++;
          }
        }

        //create QgsGeometry and use it for intersection test
        //if geometry is to be fetched, it is attached to the feature, otherwise we delete it
        QgsGeometry* theGeometry = new QgsGeometry();
        theGeometry->fromWkb(( unsigned char * )geo, 9 + 16 * totalPoints );
        bool intersection = theGeometry->intersects( b );//use geos for precise intersection test

        if ( !intersection ) //no intersection, delete geometry and move on
        {
          delete theGeometry;
        }
        else //intersection
        {
          if ( mFetchGeom )
          {
            feature.setGeometry( theGeometry );
          }
          else
          {
            delete theGeometry;
          }
          feature.setFeatureId( trk->id );
          result = true;

          feature.setValid( true );

          // add attributes if they are wanted
          for ( iter = mAttributesToFetch.begin(); iter != mAttributesToFetch.end(); ++iter )
          {
            switch ( *iter )
            {
              case NameAttr:
                feature.addAttribute( NameAttr, QVariant( trk->name ) );
                break;
              case NumAttr:
                if ( trk->number != std::numeric_limits<int>::max() )
                  feature.addAttribute( NumAttr, QVariant( trk->number ) );
                break;
              case CmtAttr:
                feature.addAttribute( CmtAttr, QVariant( trk->cmt ) );
                break;
              case DscAttr:
                feature.addAttribute( DscAttr, QVariant( trk->desc ) );
                break;
              case SrcAttr:
                feature.addAttribute( SrcAttr, QVariant( trk->src ) );
                break;
              case URLAttr:
                feature.addAttribute( URLAttr, QVariant( trk->url ) );
                break;
              case URLNameAttr:
                feature.addAttribute( URLNameAttr, QVariant( trk->urlname ) );
                break;
            }
          }

          ++mTrkIter;
          break;
        }
      }

    }
  }
  if ( result )
  {
    feature.setValid( true );
  }
  return result;
}