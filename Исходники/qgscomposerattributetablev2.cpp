bool QgsComposerAttributeTableV2::getTableContents( QgsComposerTableContents &contents )
{
  contents.clear();

  if (( mSource == QgsComposerAttributeTableV2::AtlasFeature || mSource == QgsComposerAttributeTableV2::RelationChildren )
      && !mComposition->atlasComposition().enabled() )
  {
    //source mode requires atlas, but atlas disabled
    return false;
  }

  QgsVectorLayer* layer = sourceLayer();

  if ( !layer )
  {
    //no source layer
    return false;
  }

  //prepare filter expression
  std::auto_ptr<QgsExpression> filterExpression;
  bool activeFilter = false;
  if ( mFilterFeatures && !mFeatureFilter.isEmpty() )
  {
    filterExpression = std::auto_ptr<QgsExpression>( new QgsExpression( mFeatureFilter ) );
    if ( !filterExpression->hasParserError() )
    {
      activeFilter = true;
    }
  }

  QgsRectangle selectionRect;
  if ( mComposerMap && mShowOnlyVisibleFeatures )
  {
    selectionRect = *mComposerMap->currentMapExtent();
    if ( layer && mComposition->mapSettings().hasCrsTransformEnabled() )
    {
      //transform back to layer CRS
      QgsCoordinateTransform coordTransform( layer->crs(), mComposition->mapSettings().destinationCrs() );
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

  if ( mSource == QgsComposerAttributeTableV2::RelationChildren )
  {
    QgsRelation relation = QgsProject::instance()->relationManager()->relation( mRelationId );
    QgsFeature* atlasFeature = mComposition->atlasComposition().currentFeature();
    if ( atlasFeature )
    {
      req = relation.getRelatedFeaturesRequest( *atlasFeature );
    }
    else
    {
      //no atlas feature, so empty table
      return true;
    }
  }

  if ( !selectionRect.isEmpty() )
    req.setFilterRect( selectionRect );

  req.setFlags( mShowOnlyVisibleFeatures ? QgsFeatureRequest::ExactIntersect : QgsFeatureRequest::NoFlags );

  if ( mSource == QgsComposerAttributeTableV2::AtlasFeature
       && mComposition->atlasComposition().enabled() )
  {
    //source mode is current atlas feature
    QgsFeature* atlasFeature = mComposition->atlasComposition().currentFeature();
    if ( atlasFeature )
    {
      req.setFilterFid( atlasFeature->id() );
    }
    else
    {
      //no atlas feature, so empty table
      return true;
    }
  }

  QgsFeature f;
  int counter = 0;
  QgsFeatureIterator fit = layer->getFeatures( req );

  while ( fit.nextFeature( f ) && counter < mMaximumNumberOfFeatures )
  {
    //check feature against filter
    if ( activeFilter )
    {
      QVariant result = filterExpression->evaluate( &f, layer->pendingFields() );
      // skip this feature if the filter evaluation is false
      if ( !result.toBool() )
      {
        continue;
      }
    }
    //check against atlas feature intersection
    if ( mFilterToAtlasIntersection )
    {
      if ( !f.geometry() || ! mComposition->atlasComposition().enabled() )
      {
        continue;
      }
      QgsFeature* atlasFeature = mComposition->atlasComposition().currentFeature();
      if ( !atlasFeature || !atlasFeature->geometry() ||
           !f.geometry()->intersects( atlasFeature->geometry() ) )
      {
        //feature falls outside current atlas feature
        continue;
      }
    }

    QgsComposerTableRow currentRow;

    QList<QgsComposerTableColumn*>::const_iterator columnIt = mColumns.constBegin();
    for ( ; columnIt != mColumns.constEnd(); ++columnIt )
    {
      int idx = layer->fieldNameIndex(( *columnIt )->attribute() );
      if ( idx != -1 )
      {
        currentRow << f.attributes()[idx];
      }
      else
      {
        // Lets assume it's an expression
        QgsExpression* expression = new QgsExpression(( *columnIt )->attribute() );
        expression->setCurrentRowNumber( counter + 1 );
        expression->prepare( layer->pendingFields() );
        QVariant value = expression->evaluate( f ) ;
        currentRow << value;
      }
    }

    if ( !mShowUniqueRowsOnly || !contentsContainsRow( contents, currentRow ) )
    {
      contents << currentRow;
      ++counter;
    }
  }

  //sort the list, starting with the last attribute
  QgsComposerAttributeTableCompareV2 c;
  QList< QPair<int, bool> > sortColumns = sortAttributes();
  for ( int i = sortColumns.size() - 1; i >= 0; --i )
  {
    c.setSortColumn( sortColumns.at( i ).first );
    c.setAscending( sortColumns.at( i ).second );
    qStableSort( contents.begin(), contents.end(), c );
  }

  recalculateTableSize();
  return true;
}