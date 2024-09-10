bool QgsComposerAttributeTable::getFeatureAttributes( QList<QgsAttributeMap> &attributeMaps )
{
  if ( !mVectorLayer )
  {
    return false;
  }

  QScopedPointer< QgsExpressionContext > context( createExpressionContext() );
  context->setFields( mVectorLayer->fields() );

  attributeMaps.clear();

  //prepare filter expression
  QScopedPointer<QgsExpression> filterExpression;
  bool activeFilter = false;
  if ( mFilterFeatures && !mFeatureFilter.isEmpty() )
  {
    filterExpression.reset( new QgsExpression( mFeatureFilter ) );
    if ( !filterExpression->hasParserError() )
    {
      activeFilter = true;
    }
  }

  QgsRectangle selectionRect;
  if ( mComposerMap && mShowOnlyVisibleFeatures )
  {
    selectionRect = *mComposerMap->currentMapExtent();
    if ( mComposition->mapSettings().hasCrsTransformEnabled() )
    {
      //transform back to layer CRS
      QgsCoordinateTransform coordTransform( mVectorLayer->crs(), mComposition->mapSettings().destinationCrs() );
      try
      {
        selectionRect = coordTransform.transformBoundingBox( selectionRect, QgsCoordinateTransform::ReverseTransform );
      }
      catch ( QgsCsException &cse )
      {
        Q_UNUSED( cse );
        return false;
      }
    }
  }

  QgsFeatureRequest req;
  if ( !selectionRect.isEmpty() )
    req.setFilterRect( selectionRect );

  req.setFlags( mShowOnlyVisibleFeatures ? QgsFeatureRequest::ExactIntersect : QgsFeatureRequest::NoFlags );

  QgsFeature f;
  int counter = 0;
  QgsFeatureIterator fit = mVectorLayer->getFeatures( req );

  while ( fit.nextFeature( f ) && counter < mMaximumNumberOfFeatures )
  {
    context->setFeature( f );
    //check feature against filter
    if ( activeFilter && !filterExpression.isNull() )
    {
      QVariant result = filterExpression->evaluate( context.data() );
      // skip this feature if the filter evaluation is false
      if ( !result.toBool() )
      {
        continue;
      }
    }

    attributeMaps.push_back( QgsAttributeMap() );

    QList<QgsComposerTableColumn*>::const_iterator columnIt = mColumns.constBegin();
    int i = 0;
    for ( ; columnIt != mColumns.constEnd(); ++columnIt )
    {
      int idx = mVectorLayer->fieldNameIndex(( *columnIt )->attribute() );
      if ( idx != -1 )
      {
        attributeMaps.last().insert( i, f.attributes().at( idx ) );
      }
      else
      {
        // Lets assume it's an expression
        QgsExpression* expression = new QgsExpression(( *columnIt )->attribute() );
        context->lastScope()->setVariable( QString( "row_number" ), counter + 1 );
        expression->prepare( context.data() );
        QVariant value = expression->evaluate( context.data() );
        attributeMaps.last().insert( i, value.toString() );
      }

      i++;
    }
    ++counter;
  }

  //sort the list, starting with the last attribute
  QgsComposerAttributeTableCompare c;
  QList< QPair<int, bool> > sortColumns = sortAttributes();
  for ( int i = sortColumns.size() - 1; i >= 0; --i )
  {
    c.setSortColumn( sortColumns.at( i ).first );
    c.setAscending( sortColumns.at( i ).second );
    qStableSort( attributeMaps.begin(), attributeMaps.end(), c );
  }

  adjustFrameToSize();
  return true;
}