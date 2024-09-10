void QgsVectorLayerFeatureIterator::FetchJoinInfo::addJoinedAttributesDirect( QgsFeature& f, const QVariant& joinValue ) const
{
  // no memory cache, query the joined values by setting substring
  QString subsetString = joinLayer->dataProvider()->subsetString(); // provider might already have a subset string
  QString bkSubsetString = subsetString;
  if ( !subsetString.isEmpty() )
  {
    subsetString.append( " AND " );
  }

  QString joinFieldName;
  if ( joinInfo->joinFieldName.isEmpty() && joinInfo->joinFieldIndex >= 0 && joinInfo->joinFieldIndex < joinLayer->pendingFields().count() )
    joinFieldName = joinLayer->pendingFields().field( joinInfo->joinFieldIndex ).name();   // for compatibility with 1.x
  else
    joinFieldName = joinInfo->joinFieldName;

  subsetString.append( "\"" + joinFieldName + "\"" + " = " + "\"" + joinValue.toString() + "\"" );
  joinLayer->dataProvider()->setSubsetString( subsetString, false );

  // select (no geometry)
  QgsFeatureRequest request;
  request.setFlags( QgsFeatureRequest::NoGeometry );
  request.setSubsetOfAttributes( attributes );
  QgsFeatureIterator fi = joinLayer->getFeatures( request );

  // get first feature
  QgsFeature fet;
  if ( fi.nextFeature( fet ) )
  {
    int index = indexOffset;
    const QgsAttributes& attr = fet.attributes();
    for ( int i = 0; i < attr.count(); ++i )
    {
      if ( i == joinField )
        continue;

      f.setAttribute( index++, attr[i] );
    }
  }
  else
  {
    // no suitable join feature found, keeping empty (null) attributes
  }

  joinLayer->dataProvider()->setSubsetString( bkSubsetString, false );
}