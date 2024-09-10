void QgsMapToolReshape::canvasReleaseEvent( QMouseEvent * e )
{
  //check if we operate on a vector layer //todo: move this to a function in parent class to avoid duplication
  QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>( mCanvas->currentLayer() );

  if ( !vlayer )
  {
    QMessageBox::information( 0, tr( "Not a vector layer" ),
                              tr( "The current layer is not a vector layer" ) );
    return;
  }

  if ( !vlayer->isEditable() )
  {
    QMessageBox::information( 0, tr( "Layer not editable" ),
                              tr( "Cannot edit the vector layer. Use 'Toggle Editing' to make it editable." )
                            );
    return;
  }

  //add point to list and to rubber band
  int error = addVertex( e->pos() );
  if ( error == 1 )
  {
    //current layer is not a vector layer
    return;
  }
  else if ( error == 2 )
  {
    //problem with coordinate transformation
    QMessageBox::information( 0, tr( "Coordinate transform error" ),
                              tr( "Cannot transform the point to the layers coordinate system" ) );
    return;
  }

  if ( e->button() == Qt::LeftButton )
  {
    startCapturing();
  }
  else if ( e->button() == Qt::RightButton )
  {
    //find out bounding box of mCaptureList
    if ( size() < 1 )
    {
      stopCapturing();
      return;
    }
    QgsPoint firstPoint = points().at( 0 );
    QgsRectangle bbox( firstPoint.x(), firstPoint.y(), firstPoint.x(), firstPoint.y() );
    for ( int i = 1; i < size(); ++i )
    {
      bbox.combineExtentWith( points().at( i ).x(), points().at( i ).y() );
    }

    //query all the features that intersect bounding box of capture line
    vlayer->select( QgsAttributeList(), bbox, true, false );
    QgsFeature f;
    int reshapeReturn;
    bool reshapeDone = false;

    vlayer->beginEditCommand( tr( "Reshape" ) );
    while ( vlayer->nextFeature( f ) )
    {
      //query geometry
      //call geometry->reshape(mCaptureList)
      //register changed geometry in vector layer
      QgsGeometry* geom = f.geometry();
      if ( geom )
      {
        reshapeReturn = geom->reshapeGeometry( points() );
        if ( reshapeReturn == 0 )
        {
          vlayer->changeGeometry( f.id(), geom );
          reshapeDone = true;
        }
      }
    }

    if ( reshapeDone )
    {
      vlayer->endEditCommand();
    }
    else
    {
      vlayer->destroyEditCommand();
    }

    stopCapturing();
  }
}