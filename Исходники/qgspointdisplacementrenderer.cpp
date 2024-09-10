void QgsPointDisplacementRenderer::createDisplacementGroups( QgsVectorLayer* vlayer, const QgsRectangle& viewExtent )
{
  if ( !vlayer || ( vlayer->wkbType() != QGis::WKBPoint && vlayer->wkbType() != QGis::WKBPoint25D ) )
  {
    return;
  }

  mDisplacementGroups.clear();
  mDisplacementIds.clear();

  //use a spatial index to check if there is already a point at a position
  QgsSpatialIndex spatialIndex;

  //attributes
  QgsAttributeList attList;
  QList<QString> attributeStrings = usedAttributes();
  QList<QString>::const_iterator attStringIt = attributeStrings.constBegin();
  for ( ; attStringIt != attributeStrings.constEnd(); ++attStringIt )
  {
    attList.push_back( vlayer->fieldNameIndex( *attStringIt ) );
  }

  QgsFeature f;
  QList<int> intersectList;

  vlayer->select( attList, viewExtent, true, false );
  while ( vlayer->nextFeature( f ) )
  {
    intersectList.clear();

    //check, if there is already a point at that position
    if ( f.geometry() )
    {
      intersectList = spatialIndex.intersects( searchRect( f.geometry()->asPoint() ) );
      if ( intersectList.empty() )
      {
        spatialIndex.insertFeature( f );
      }
      else
      {
        //go through all the displacement group maps and search an entry where the id equals the result of the spatial search
        int existingEntry = intersectList.at( 0 );
        bool found = false;
        QList<QMap<int, QgsFeature> >::iterator it = mDisplacementGroups.begin();
        for ( ; it != mDisplacementGroups.end(); ++it )
        {
          if ( it->size() > 0 && it->contains( existingEntry ) )
          {
            found = true;
            QgsFeature feature;
            it->insert( f.id(), f );
            mDisplacementIds.insert( f.id() );
            break;
          }
        }

        if ( !found )//insert the already existing feature and the new one into a map
        {
          QMap<int, QgsFeature> newMap;
          QgsFeature existingFeature;
          vlayer->featureAtId( existingEntry, existingFeature );
          newMap.insert( existingEntry, existingFeature );
          mDisplacementIds.insert( existingEntry );
          newMap.insert( f.id(), f );
          mDisplacementIds.insert( f.id() );
          mDisplacementGroups.push_back( newMap );
        }
      }
    }
  }
  //refresh the selection because the vector layer is going to step through all features now
  vlayer->select( attList, viewExtent, true, false );
}