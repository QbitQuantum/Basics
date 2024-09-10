int QgsTransectSample::createSample( QProgressDialog* pd )
{
  Q_UNUSED( pd );

  if ( !mStrataLayer || !mStrataLayer->isValid() )
  {
    return 1;
  }

  if ( !mBaselineLayer || !mBaselineLayer->isValid() )
  {
    return 2;
  }

  //stratum id is not necessarily an integer
  QVariant::Type stratumIdType = QVariant::Int;
  if ( !mStrataIdAttribute.isEmpty() )
  {
    stratumIdType = mStrataLayer->pendingFields().field( mStrataIdAttribute ).type();
  }

  //create vector file writers for output
  QgsFields outputPointFields;
  outputPointFields.append( QgsField( "id", stratumIdType ) );
  outputPointFields.append( QgsField( "station_id", QVariant::Int ) );
  outputPointFields.append( QgsField( "stratum_id", stratumIdType ) );
  outputPointFields.append( QgsField( "station_code", QVariant::String ) );
  outputPointFields.append( QgsField( "start_lat", QVariant::Double ) );
  outputPointFields.append( QgsField( "start_long", QVariant::Double ) );

  QgsVectorFileWriter outputPointWriter( mOutputPointLayer, "utf-8", outputPointFields, QGis::WKBPoint,
                                         &( mStrataLayer->crs() ) );
  if ( outputPointWriter.hasError() != QgsVectorFileWriter::NoError )
  {
    return 3;
  }

  outputPointFields.append( QgsField( "bearing", QVariant::Double ) ); //add bearing attribute for lines
  QgsVectorFileWriter outputLineWriter( mOutputLineLayer, "utf-8", outputPointFields, QGis::WKBLineString,
                                        &( mStrataLayer->crs() ) );
  if ( outputLineWriter.hasError() != QgsVectorFileWriter::NoError )
  {
    return 4;
  }

  QgsFields usedBaselineFields;
  usedBaselineFields.append( QgsField( "stratum_id", stratumIdType ) );
  usedBaselineFields.append( QgsField( "ok", QVariant::String ) );
  QgsVectorFileWriter usedBaselineWriter( mUsedBaselineLayer, "utf-8", usedBaselineFields, QGis::WKBLineString,
                                          &( mStrataLayer->crs() ) );
  if ( usedBaselineWriter.hasError() != QgsVectorFileWriter::NoError )
  {
    return 5;
  }

  //debug: write clipped buffer bounds with stratum id to same directory as out_point
  QFileInfo outputPointInfo( mOutputPointLayer );
  QString bufferClipLineOutput = outputPointInfo.absolutePath() + "/out_buffer_clip_line.shp";
  QgsFields bufferClipLineFields;
  bufferClipLineFields.append( QgsField( "id", stratumIdType ) );
  QgsVectorFileWriter bufferClipLineWriter( bufferClipLineOutput, "utf-8", bufferClipLineFields, QGis::WKBLineString, &( mStrataLayer->crs() ) );

  //configure distanceArea depending on minDistance units and output CRS
  QgsDistanceArea distanceArea;
  distanceArea.setSourceCrs( mStrataLayer->crs().srsid() );
  if ( mMinDistanceUnits == Meters )
  {
    distanceArea.setEllipsoidalMode( true );
  }
  else
  {
    distanceArea.setEllipsoidalMode( false );
  }

  //possibility to transform output points to lat/long
  QgsCoordinateTransform toLatLongTransform( mStrataLayer->crs(), QgsCoordinateReferenceSystem( 4326, QgsCoordinateReferenceSystem::EpsgCrsId ) );

  //init random number generator
  mt_srand( QTime::currentTime().msec() );

  QgsFeatureRequest fr;
  fr.setSubsetOfAttributes( QStringList() << mStrataIdAttribute << mMinDistanceAttribute << mNPointsAttribute, mStrataLayer->pendingFields() );
  QgsFeatureIterator strataIt = mStrataLayer->getFeatures( fr );

  QgsFeature fet;
  int nTotalTransects = 0;
  int nFeatures = 0;

  if ( pd )
  {
    pd->setMaximum( mStrataLayer->featureCount() );
  }

  while ( strataIt.nextFeature( fet ) )
  {
    if ( pd )
    {
      pd->setValue( nFeatures );
    }
    if ( pd && pd->wasCanceled() )
    {
      break;
    }

    if ( !fet.constGeometry() )
    {
      continue;
    }
    const QgsGeometry* strataGeom = fet.constGeometry();

    //find baseline for strata
    QVariant strataId = fet.attribute( mStrataIdAttribute );
    QgsGeometry* baselineGeom = findBaselineGeometry( strataId.isValid() ? strataId : -1 );
    if ( !baselineGeom )
    {
      continue;
    }

    double minDistance = fet.attribute( mMinDistanceAttribute ).toDouble();
    double minDistanceLayerUnits = minDistance;
    //if minDistance is in meters and the data in degrees, we need to apply a rough conversion for the buffer distance
    double bufferDist = bufferDistance( minDistance );
    if ( mMinDistanceUnits == Meters && mStrataLayer->crs().mapUnits() == QGis::DecimalDegrees )
    {
      minDistanceLayerUnits = minDistance / 111319.9;
    }

    QgsGeometry* clippedBaseline = strataGeom->intersection( baselineGeom );
    if ( !clippedBaseline || clippedBaseline->wkbType() == QGis::WKBUnknown )
    {
      delete clippedBaseline;
      continue;
    }
    QgsGeometry* bufferLineClipped = clipBufferLine( strataGeom, clippedBaseline, bufferDist );
    if ( !bufferLineClipped )
    {
      delete clippedBaseline;
      continue;
    }

    //save clipped baseline to file
    QgsFeature blFeature;
    blFeature.setGeometry( *clippedBaseline );
    blFeature.setAttribute( "stratum_id", strataId );
    blFeature.setAttribute( "ok", "f" );
    usedBaselineWriter.addFeature( blFeature );

    //start loop to create random points along the baseline
    int nTransects = fet.attribute( mNPointsAttribute ).toInt();
    int nCreatedTransects = 0;
    int nIterations = 0;
    int nMaxIterations = nTransects * 50;

    QgsSpatialIndex sIndex; //to check minimum distance
    QMap< QgsFeatureId, QgsGeometry* > lineFeatureMap;

    while ( nCreatedTransects < nTransects && nIterations < nMaxIterations )
    {
      double randomPosition = (( double )mt_rand() / MD_RAND_MAX ) * clippedBaseline->length();
      QgsGeometry* samplePoint = clippedBaseline->interpolate( randomPosition );
      ++nIterations;
      if ( !samplePoint )
      {
        continue;
      }
      QgsPoint sampleQgsPoint = samplePoint->asPoint();
      QgsPoint latLongSamplePoint = toLatLongTransform.transform( sampleQgsPoint );

      QgsFeature samplePointFeature;
      samplePointFeature.setGeometry( samplePoint );
      samplePointFeature.setAttribute( "id", nTotalTransects + 1 );
      samplePointFeature.setAttribute( "station_id", nCreatedTransects + 1 );
      samplePointFeature.setAttribute( "stratum_id", strataId );
      samplePointFeature.setAttribute( "station_code", strataId.toString() + "_" + QString::number( nCreatedTransects + 1 ) );
      samplePointFeature.setAttribute( "start_lat", latLongSamplePoint.y() );
      samplePointFeature.setAttribute( "start_long", latLongSamplePoint.x() );

      //find closest point on clipped buffer line
      QgsPoint minDistPoint;

      int afterVertex;
      if ( bufferLineClipped->closestSegmentWithContext( sampleQgsPoint, minDistPoint, afterVertex ) < 0 )
      {
        continue;
      }

      //bearing between sample point and min dist point (transect direction)
      double bearing = distanceArea.bearing( sampleQgsPoint, minDistPoint ) / M_PI * 180.0;

      QgsPolyline sampleLinePolyline;
      QgsPoint ptFarAway( sampleQgsPoint.x() + ( minDistPoint.x() - sampleQgsPoint.x() ) * 1000000,
                          sampleQgsPoint.y() + ( minDistPoint.y() - sampleQgsPoint.y() ) * 1000000 );
      QgsPolyline lineFarAway;
      lineFarAway << sampleQgsPoint << ptFarAway;
      QgsGeometry* lineFarAwayGeom = QgsGeometry::fromPolyline( lineFarAway );
      QgsGeometry* lineClipStratum = lineFarAwayGeom->intersection( strataGeom );
      if ( !lineClipStratum )
      {
        delete lineFarAwayGeom; delete lineClipStratum;
        continue;
      }

      //cancel if distance between sample point and line is too large (line does not start at point
      if ( lineClipStratum->distance( *samplePoint ) > 0.000001 )
      {
        delete lineFarAwayGeom; delete lineClipStratum;
        continue;
      }

      //if lineClipStratum is a multiline, take the part line closest to sampleQgsPoint
      if ( lineClipStratum->wkbType() == QGis::WKBMultiLineString
           || lineClipStratum->wkbType() == QGis::WKBMultiLineString25D )
      {
        QgsGeometry* singleLine = closestMultilineElement( sampleQgsPoint, lineClipStratum );
        if ( singleLine )
        {
          delete lineClipStratum;
          lineClipStratum = singleLine;
        }
      }

      //cancel if length of lineClipStratum is too small
      double transectLength = distanceArea.measure( lineClipStratum );
      if ( transectLength < mMinTransectLength )
      {
        delete lineFarAwayGeom; delete lineClipStratum;
        continue;
      }

      //search closest existing profile. Cancel if dist < minDist
      if ( otherTransectWithinDistance( lineClipStratum, minDistanceLayerUnits, minDistance, sIndex, lineFeatureMap, distanceArea ) )
      {
        delete lineFarAwayGeom; delete lineClipStratum;
        continue;
      }

      QgsFeatureId fid( nCreatedTransects );
      QgsFeature sampleLineFeature( fid );
      sampleLineFeature.setGeometry( lineClipStratum );
      sampleLineFeature.setAttribute( "id", nTotalTransects + 1 );
      sampleLineFeature.setAttribute( "station_id", nCreatedTransects + 1 );
      sampleLineFeature.setAttribute( "stratum_id", strataId );
      sampleLineFeature.setAttribute( "station_code", strataId.toString() + "_" + QString::number( nCreatedTransects + 1 ) );
      sampleLineFeature.setAttribute( "start_lat", latLongSamplePoint.y() );
      sampleLineFeature.setAttribute( "start_long", latLongSamplePoint.x() );
      sampleLineFeature.setAttribute( "bearing", bearing );
      outputLineWriter.addFeature( sampleLineFeature );

      //add point to file writer here.
      //It can only be written if the corresponding transect has been as well
      outputPointWriter.addFeature( samplePointFeature );

      sIndex.insertFeature( sampleLineFeature );
      Q_NOWARN_DEPRECATED_PUSH
      lineFeatureMap.insert( fid, sampleLineFeature.geometryAndOwnership() );
      Q_NOWARN_DEPRECATED_POP

      delete lineFarAwayGeom;
      ++nTotalTransects;
      ++nCreatedTransects;
    }
    delete clippedBaseline;

    QgsFeature bufferClipFeature;
    bufferClipFeature.setGeometry( bufferLineClipped );
    bufferClipFeature.setAttribute( "id", strataId );
    bufferClipLineWriter.addFeature( bufferClipFeature );
    //delete bufferLineClipped;

    //delete all line geometries in spatial index
    QMap< QgsFeatureId, QgsGeometry* >::iterator featureMapIt = lineFeatureMap.begin();
    for ( ; featureMapIt != lineFeatureMap.end(); ++featureMapIt )
    {
      delete( featureMapIt.value() );
    }
    lineFeatureMap.clear();
    delete baselineGeom;

    ++nFeatures;
  }

  if ( pd )
  {
    pd->setValue( mStrataLayer->featureCount() );
  }

  return 0;
}