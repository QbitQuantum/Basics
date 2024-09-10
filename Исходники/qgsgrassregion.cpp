void QgsGrassRegionEdit::transform( QgsMapCanvas *, QVector<QgsPointXY> &points, const QgsCoordinateTransform &coordinateTransform, QgsCoordinateTransform::TransformDirection direction )
{
  //! Coordinate transform
  //QgsDebugMsg ( "srcCrs = " +  coordinateTransform->sourceCrs().toWkt() );
  //QgsDebugMsg ( "destCrs = " +  coordinateTransform->destCRS().toWkt() );
  try
  {
    for ( int i = 0; i < points.size(); i++ )
    {
      points[i] = coordinateTransform.transform( points[i], direction );
    }
  }
  catch ( QgsCsException &cse )
  {
    Q_UNUSED( cse );
    QgsDebugMsg( QString( "transformation failed: %1" ).arg( cse.what() ) );
  }
}