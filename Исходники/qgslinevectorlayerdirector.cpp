void QgsLineVectorLayerDirector::makeGraph( QgsGraphBuilderInterface *builder, const QVector< QgsPoint >& additionalPoints,
    QVector< QgsPoint >& tiedPoint ) const
{
  QgsVectorLayer *vl = mVectorLayer;

  if ( vl == NULL )
    return;

  int featureCount = ( int ) vl->featureCount() * 2;
  int step = 0;

  QgsCoordinateTransform ct;
  ct.setSourceCrs( vl->crs() );
  if ( builder->coordinateTransformationEnabled() )
  {
    ct.setDestCRS( builder->destinationCrs() );
  }
  else
  {
    ct.setDestCRS( vl->crs() );
  }

  tiedPoint = QVector< QgsPoint >( additionalPoints.size(), QgsPoint( 0.0, 0.0 ) );

  TiePointInfo tmpInfo;
  tmpInfo.mLength = std::numeric_limits<double>::infinity();

  QVector< TiePointInfo > pointLengthMap( additionalPoints.size(), tmpInfo );
  QVector< TiePointInfo >::iterator pointLengthIt;

  //Graph's points;
  QVector< QgsPoint > points;

  QgsFeatureIterator fit = vl->getFeatures( QgsFeatureRequest().setSubsetOfAttributes( QgsAttributeList() ) );

  // begin: tie points to the graph
  QgsAttributeList la;
  QgsFeature feature;
  while ( fit.nextFeature( feature ) )
  {
    QgsMultiPolyline mpl;
    if ( feature.constGeometry()->wkbType() == QGis::WKBMultiLineString )
      mpl = feature.constGeometry()->asMultiPolyline();
    else if ( feature.constGeometry()->wkbType() == QGis::WKBLineString )
      mpl.push_back( feature.constGeometry()->asPolyline() );

    QgsMultiPolyline::iterator mplIt;
    for ( mplIt = mpl.begin(); mplIt != mpl.end(); ++mplIt )
    {
      QgsPoint pt1, pt2;
      bool isFirstPoint = true;
      QgsPolyline::iterator pointIt;
      for ( pointIt = mplIt->begin(); pointIt != mplIt->end(); ++pointIt )
      {
        pt2 = ct.transform( *pointIt );
        points.push_back( pt2 );

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
              info.mLength = additionalPoints[ i ].sqrDistToSegment( pt1.x(), pt1.y(),
                             pt2.x(), pt2.y(), info.mTiedPoint );
            }

            if ( pointLengthMap[ i ].mLength > info.mLength )
            {
              Q_UNUSED( info.mTiedPoint );
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

  // add tied point to graph
  int i = 0;
  for ( i = 0; i < tiedPoint.size(); ++i )
  {
    if ( tiedPoint[ i ] != QgsPoint( 0.0, 0.0 ) )
    {
      points.push_back( tiedPoint [ i ] );
    }
  }

  QgsPointCompare pointCompare( builder->topologyTolerance() );

  qSort( points.begin(), points.end(), pointCompare );
  QVector< QgsPoint >::iterator tmp = std::unique( points.begin(), points.end() );
  points.resize( tmp - points.begin() );

  for ( i = 0;i < points.size();++i )
    builder->addVertex( i, points[ i ] );

  for ( i = 0; i < tiedPoint.size() ; ++i )
    tiedPoint[ i ] = *( my_binary_search( points.begin(), points.end(), tiedPoint[ i ], pointCompare ) );

  qSort( pointLengthMap.begin(), pointLengthMap.end(), TiePointInfoCompare );

  {
    // fill attribute list 'la'
    QgsAttributeList tmpAttr;
    if ( mDirectionFieldId != -1 )
    {
      tmpAttr.push_back( mDirectionFieldId );
    }

    QList< QgsArcProperter* >::const_iterator it;
    QgsAttributeList::const_iterator it2;

    for ( it = mProperterList.begin(); it != mProperterList.end(); ++it )
    {
      QgsAttributeList tmp = ( *it )->requiredAttributes();
      for ( it2 = tmp.begin(); it2 != tmp.end(); ++it2 )
      {
        tmpAttr.push_back( *it2 );
      }
    }
    qSort( tmpAttr.begin(), tmpAttr.end() );

    int lastAttrId = -1;
    for ( it2 = tmpAttr.begin(); it2 != tmpAttr.end(); ++it2 )
    {
      if ( *it2 == lastAttrId )
      {
        continue;
      }

      la.push_back( *it2 );

      lastAttrId = *it2;
    }
  } // end fill attribute list 'la'

  // begin graph construction
  fit = vl->getFeatures( QgsFeatureRequest().setSubsetOfAttributes( la ) );
  while ( fit.nextFeature( feature ) )
  {
    int directionType = mDefaultDirection;

    // What direction have feature?
    QString str = feature.attribute( mDirectionFieldId ).toString();
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

    // begin features segments and add arc to the Graph;
    QgsMultiPolyline mpl;
    if ( feature.constGeometry()->wkbType() == QGis::WKBMultiLineString )
      mpl = feature.constGeometry()->asMultiPolyline();
    else if ( feature.constGeometry()->wkbType() == QGis::WKBLineString )
      mpl.push_back( feature.constGeometry()->asPolyline() );

    QgsMultiPolyline::iterator mplIt;
    for ( mplIt = mpl.begin(); mplIt != mpl.end(); ++mplIt )
    {
      QgsPoint pt1, pt2;

      bool isFirstPoint = true;
      QgsPolyline::iterator pointIt;
      for ( pointIt = mplIt->begin(); pointIt != mplIt->end(); ++pointIt )
      {
        pt2 = ct.transform( *pointIt );

        if ( !isFirstPoint )
        {
          std::map< double, QgsPoint > pointsOnArc;
          pointsOnArc[ 0.0 ] = pt1;
          pointsOnArc[ pt1.sqrDist( pt2 )] = pt2;

          TiePointInfo t;
          t.mFirstPoint = pt1;
          t.mLastPoint  = pt2;
          pointLengthIt = my_binary_search( pointLengthMap.begin(), pointLengthMap.end(), t, TiePointInfoCompare );

          if ( pointLengthIt != pointLengthMap.end() )
          {
            QVector< TiePointInfo >::iterator it;
            for ( it = pointLengthIt; it - pointLengthMap.begin() >= 0; --it )
            {
              if ( it->mFirstPoint == pt1 && it->mLastPoint == pt2 )
              {
                pointsOnArc[ pt1.sqrDist( it->mTiedPoint )] = it->mTiedPoint;
              }
            }
            for ( it = pointLengthIt + 1; it != pointLengthMap.end(); ++it )
            {
              if ( it->mFirstPoint == pt1 && it->mLastPoint == pt2 )
              {
                pointsOnArc[ pt1.sqrDist( it->mTiedPoint )] = it->mTiedPoint;
              }
            }
          }

          std::map< double, QgsPoint >::iterator pointsIt;
          QgsPoint pt1;
          QgsPoint pt2;
          int pt1idx = -1, pt2idx = -1;
          bool isFirstPoint = true;
          for ( pointsIt = pointsOnArc.begin(); pointsIt != pointsOnArc.end(); ++pointsIt )
          {
            pt2 = pointsIt->second;
            tmp = my_binary_search( points.begin(), points.end(), pt2, pointCompare );
            pt2 = *tmp;
            pt2idx = tmp - points.begin();

            if ( !isFirstPoint && pt1 != pt2 )
            {
              double distance = builder->distanceArea()->measureLine( pt1, pt2 );
              QVector< QVariant > prop;
              QList< QgsArcProperter* >::const_iterator it;
              for ( it = mProperterList.begin(); it != mProperterList.end(); ++it )
              {
                prop.push_back(( *it )->property( distance, feature ) );
              }

              if ( directionType == 1 ||
                   directionType == 3 )
              {
                builder->addArc( pt1idx, pt1, pt2idx, pt2, prop );
              }
              if ( directionType == 2 ||
                   directionType == 3 )
              {
                builder->addArc( pt2idx, pt2, pt1idx, pt1, prop );
              }
            }
            pt1idx = pt2idx;
            pt1 = pt2;
            isFirstPoint = false;
          }
        } // if ( !isFirstPoint )
        pt1 = pt2;
        isFirstPoint = false;
      } // for (it = pl.begin(); it != pl.end(); ++it)
    }
    emit buildProgress( ++step, featureCount );
  } // while( vl->nextFeature(feature) )
} // makeGraph( QgsGraphBuilderInterface *builder, const QVector< QgsPoint >& additionalPoints, QVector< QgsPoint >& tiedPoint )