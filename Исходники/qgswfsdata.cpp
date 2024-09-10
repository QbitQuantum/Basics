void QgsWFSData::calculateExtentFromFeatures() const
{
  if ( mFeatures.size() < 1 )
  {
    return;
  }

  QgsRectangle bbox;

  QgsFeature* currentFeature = 0;
  QgsGeometry* currentGeometry = 0;
  bool bboxInitialised = false; //gets true once bbox has been set to the first geometry

  for ( int i = 0; i < mFeatures.size(); ++i )
  {
    currentFeature = mFeatures[i];
    if ( !currentFeature )
    {
      continue;
    }
    currentGeometry = currentFeature->geometry();
    if ( currentGeometry )
    {
      if ( !bboxInitialised )
      {
        bbox = currentGeometry->boundingBox();
        bboxInitialised = true;
      }
      else
      {
        bbox.unionRect( currentGeometry->boundingBox() );
      }
    }
  }
  ( *mExtent ) = bbox;
}