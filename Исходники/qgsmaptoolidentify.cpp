bool QgsMapToolIdentify::identifyRasterLayer( QgsRasterLayer *layer, int x, int y )
{
  bool res = true;

  if ( !layer )
    return false;

  QgsRasterDataProvider *dprovider = layer->dataProvider();
  if ( dprovider && ( dprovider->capabilities() & QgsRasterDataProvider::Identify ) == 0 )
    return false;

  QMap< QString, QString > attributes, derivedAttributes;
  QgsPoint idPoint = mCanvas->getCoordinateTransform()->toMapCoordinates( x, y );
  idPoint = toLayerCoordinates( layer, idPoint );
  QString type;

  if ( layer->providerType() == "wms" )
  {
    type = tr( "WMS layer" );

    //if WMS layer does not cover the view origin,
    //we need to map the view pixel coordinates
    //to WMS layer pixel coordinates
    QgsRectangle viewExtent = mCanvas->extent();
    QgsRectangle layerExtent = layer->extent();
    double mapUnitsPerPixel = mCanvas->mapUnitsPerPixel();
    if ( mapUnitsPerPixel > 0 && viewExtent.intersects( layerExtent ) )
    {
      double xMinView = viewExtent.xMinimum();
      double yMaxView = viewExtent.yMaximum();
      double xMinLayer = layerExtent.xMinimum();
      double yMaxLayer = layerExtent.yMaximum();

      idPoint.set(
        xMinView < xMinLayer ? floor( x - ( xMinLayer - xMinView ) / mapUnitsPerPixel ) : x,
        yMaxView > yMaxLayer ? floor( y - ( yMaxView - yMaxLayer ) / mapUnitsPerPixel ) : y
      );

      attributes.insert( tr( "Feature info" ), layer->identifyAsHtml( idPoint ) );
    }
    else
    {
      res = false;
    }
  }
  else
  {
    type = tr( "Raster" );
    res = layer->extent().contains( idPoint ) && layer->identify( idPoint, attributes );
  }

  if ( res )
  {
    derivedAttributes.insert( tr( "(clicked coordinate)" ), idPoint.toString() );
    results()->addFeature( layer, type, attributes, derivedAttributes );
  }

  return res;
}