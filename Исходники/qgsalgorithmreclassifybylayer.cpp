bool QgsReclassifyByLayerAlgorithm::_prepareAlgorithm( const QVariantMap &parameters, QgsProcessingContext &context, QgsProcessingFeedback * )
{
  std::unique_ptr< QgsFeatureSource >tableSource( parameterAsSource( parameters, QStringLiteral( "INPUT_TABLE" ), context ) );
  if ( !tableSource )
    throw QgsProcessingException( invalidSourceError( parameters, QStringLiteral( "INPUT_TABLE" ) ) );

  QString fieldMin = parameterAsString( parameters, QStringLiteral( "MIN_FIELD" ), context );
  mMinFieldIdx = tableSource->fields().lookupField( fieldMin );
  if ( mMinFieldIdx < 0 )
    throw QgsProcessingException( QObject::tr( "Invalid field specified for MIN_FIELD: %1" ).arg( fieldMin ) );
  QString fieldMax = parameterAsString( parameters, QStringLiteral( "MAX_FIELD" ), context );
  mMaxFieldIdx = tableSource->fields().lookupField( fieldMax );
  if ( mMaxFieldIdx < 0 )
    throw QgsProcessingException( QObject::tr( "Invalid field specified for MAX_FIELD: %1" ).arg( fieldMax ) );
  QString fieldValue = parameterAsString( parameters, QStringLiteral( "VALUE_FIELD" ), context );
  mValueFieldIdx = tableSource->fields().lookupField( fieldValue );
  if ( mValueFieldIdx < 0 )
    throw QgsProcessingException( QObject::tr( "Invalid field specified for VALUE_FIELD: %1" ).arg( fieldValue ) );

  QgsFeatureRequest request;
  request.setFlags( QgsFeatureRequest::NoGeometry );
  request.setSubsetOfAttributes( QgsAttributeList() << mMinFieldIdx << mMaxFieldIdx << mValueFieldIdx );
  mTableIterator = tableSource->getFeatures( request );

  return true;
}