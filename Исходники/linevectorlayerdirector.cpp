void RgLineVectorLayerDirector::makeGraph( RgGraphBuilder *builder, const QVector< QgsPoint >& additionalPoints,
    QVector< QgsPoint >& tiedPoint ) const
{
  QgsVectorLayer *vl = myLayer();

  if ( vl == NULL )
    return;

  int featureCount = ( int ) vl->featureCount() * 2;
  int step = 0;

  QgsCoordinateTransform ct;
  QgsDistanceArea da;
  ct.setSourceCrs( vl->crs() );

  if ( builder->coordinateTransformEnabled() )
  {
    ct.setDestCRS( builder->destinationCrs() );
    da.setProjectionsEnabled( true );
    //
    //da.setSourceCrs( builder->destinationCrs().srsid() );
    //
  }
  else
  {
    ct.setDestCRS( vl->crs() );
    da.setProjectionsEnabled( false );
  }

  tiedPoint = QVector< QgsPoint >( additionalPoints.size(), QgsPoint( 0.0, 0.0 ) );
  TiePointInfo tmpInfo;
  tmpInfo.mLength = infinity();

  QVector< TiePointInfo > pointLengthMap( additionalPoints.size(), tmpInfo );
  QVector< TiePointInfo >::iterator pointLengthIt;

  // begin: tie points to the graph
  QgsAttributeList la;
  vl->select( la );
  QgsFeature feature;
  while ( vl->nextFeature( feature ) )
  {
    QgsMultiPolyline mpl;
    if ( feature.geometry()->wkbType() == QGis::WKBLineString )
    {
      mpl.push_back( feature.geometry()->asPolyline() );
    }else if ( feature.geometry()->wkbType() == QGis::WKBMultiLineString )
    {
      mpl = feature.geometry()->asMultiPolyline();
    }

    QgsMultiPolyline::iterator mplIt;
    for ( mplIt = mpl.begin(); mplIt != mpl.end(); ++mplIt )
    {
      QgsPoint pt1, pt2;
      bool isFirstPoint = true;
      QgsPolyline::iterator pointIt;
      for ( pointIt = mplIt->begin(); pointIt != mplIt->end(); ++pointIt )
      {
        pt2 = builder->addVertex( ct.transform( *pointIt ) );
        if ( !isFirstPoint )
        {
          int i = 0;
          for ( i = 0; i != additionalPoints.size(); ++i )
          {
            TiePointInfo info;
            if ( pt1 == pt2 )
            {
              info.mLength = additionalPoints[ i ].sqrDist( pt1 );
              info.mTiedPoint = pt1;
            }
            else
            {
              info.mLength = additionalPoints[ i ].sqrDistToSegment( pt1.x(), pt1.y(), pt2.x(), pt2.y(), info.mTiedPoint );
            }
            if ( pointLengthMap[ i ].mLength > info.mLength )
            {
              info.mTiedPoint = builder->addVertex( info.mTiedPoint );
              info.mFirstPoint = pt1;
              info.mLastPoint = pt2;

              pointLengthMap[ i ] = info;
              tiedPoint[ i ] = info.mTiedPoint;
            }
          }
        }
        pt1 = pt2;
        isFirstPoint = false;
      }
    }
    emit buildProgress( ++step, featureCount );
  }
  // end: tie points to graph

  if ( mDirectionFieldId != -1 )
  {
    la.push_back( mDirectionFieldId );
  }
  if ( mSpeedFieldId != -1 )
  {
    la.push_back( mSpeedFieldId );
  }

  SpeedUnit su = SpeedUnit::byName( mSpeedUnitName );

  // begin graph construction
  vl->select( la );
  while ( vl->nextFeature( feature ) )
  {
    QgsAttributeMap attr = feature.attributeMap();
    int directionType = mDefaultDirection;
    QgsAttributeMap::const_iterator it;
    // What direction have feature?
    for ( it = attr.constBegin(); it != attr.constEnd(); ++it )
    {
      if ( it.key() != mDirectionFieldId )
      {
        continue;
      }
      QString str = it.value().toString();
      if ( str == mBothDirectionValue )
      {
        directionType = 3;
      }
      else if ( str == mDirectDirectionValue )
      {
        directionType = 1;
      }
      else if ( str == mReverseDirectionValue )
      {
        directionType = 2;
      }
    }
    // What speed have feature?
    double speed = 0.0;
    for ( it = attr.constBegin(); it != attr.constEnd(); ++it )
    {
      if ( it.key() != mSpeedFieldId )
      {
        continue;
      }
      speed = it.value().toDouble();
    }
    if ( speed <= 0.0 )
    {
      speed = mDefaultSpeed;
    }

    // begin features segments and add arc to the Graph;
    QgsMultiPolyline mpl;
    if ( feature.geometry()->wkbType() == QGis::WKBLineString )
    {
      mpl.push_back( feature.geometry()->asPolyline() );
    }else if ( feature.geometry()->wkbType() == QGis::WKBMultiLineString )
    {
      mpl = feature.geometry()->asMultiPolyline();
    }
    QgsMultiPolyline::iterator mplIt;
    for ( mplIt = mpl.begin(); mplIt != mpl.end(); ++mplIt )
    {
      QgsPoint pt1, pt2;
      bool isFirstPoint = true;
      QgsPolyline::iterator pointIt;
      for ( pointIt = mplIt->begin(); pointIt != mplIt->end(); ++pointIt )
      {
        pt2 = builder->addVertex( ct.transform( *pointIt ) );

        std::map< double, QgsPoint > pointsOnArc;
        pointsOnArc[ 0.0 ] = pt1;
        pointsOnArc[ pt1.sqrDist( pt2 )] = pt2;

        for ( pointLengthIt = pointLengthMap.begin(); pointLengthIt != pointLengthMap.end(); ++pointLengthIt )
        {
          if ( pointLengthIt->mFirstPoint == pt1 && pointLengthIt->mLastPoint == pt2 )
          {
            QgsPoint tiedPoint = pointLengthIt->mTiedPoint;
            pointsOnArc[ pt1.sqrDist( tiedPoint )] = tiedPoint;
          }
        }

        if ( !isFirstPoint )
        {
          std::map< double, QgsPoint >::iterator pointsIt;
          QgsPoint pt1;
          QgsPoint pt2;
          bool isFirstPoint = true;
          for ( pointsIt = pointsOnArc.begin(); pointsIt != pointsOnArc.end(); ++pointsIt )
          {
            pt2 = pointsIt->second;
            if ( !isFirstPoint )
            {
              double cost = da.measureLine( pt1, pt2 );
              if ( directionType == 1 ||
                   directionType == 3 )
              {
                builder->addArc( pt1, pt2, cost, speed*su.multipler(), feature.id() );
              }
              if ( directionType == 2 ||
                   directionType == 3 )
              {
                builder->addArc( pt2, pt1, cost, speed*su.multipler(), feature.id() );
              }
            }
            pt1 = pt2;
            isFirstPoint = false;
          }
        } // if ( !isFirstPoint )
        pt1 = pt2;
        isFirstPoint = false;
      }
    } // for (it = pl.begin(); it != pl.end(); ++it)
    emit buildProgress( ++step, featureCount );
  } // while( vl->nextFeature(feature) )
} // makeGraph( RgGraphBuilder *builder, const QgsRectangle& rt )