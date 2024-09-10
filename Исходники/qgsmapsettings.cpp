QgsPointXY QgsMapSettings::layerToMapCoordinates( const QgsMapLayer *layer, QgsPointXY point ) const
{
  try
  {
    QgsCoordinateTransform ct = layerTransform( layer );
    if ( ct.isValid() )
      point = ct.transform( point, QgsCoordinateTransform::ForwardTransform );
  }
  catch ( QgsCsException &cse )
  {
    QgsMessageLog::logMessage( QObject::tr( "Transform error caught: %1" ).arg( cse.what() ), QObject::tr( "CRS" ) );
  }

  return point;
}