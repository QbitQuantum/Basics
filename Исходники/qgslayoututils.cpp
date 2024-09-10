QgsRenderContext QgsLayoutUtils::createRenderContextForMap( QgsLayoutItemMap *map, QPainter *painter, double dpi )
{
  if ( !map )
  {
    QgsRenderContext context;
    context.setPainter( painter );
    if ( dpi < 0 && painter && painter->device() )
    {
      context.setScaleFactor( painter->device()->logicalDpiX() / 25.4 );
    }
    else if ( dpi > 0 )
    {
      context.setScaleFactor( dpi / 25.4 );
    }
    else
    {
      context.setScaleFactor( 3.465 ); //assume 88 dpi as standard value
    }
    return context;
  }
  else
  {
    // default to 88 dpi if no painter specified
    if ( dpi < 0 )
    {
      dpi = ( painter && painter->device() ) ? painter->device()->logicalDpiX() : 88;
    }
#if 0
    double dotsPerMM = dpi / 25.4;
// TODO
    // get map settings from reference map
    QgsRectangle extent = *( map->currentMapExtent() );
    QSizeF mapSizeMM = map->rect().size();
    QgsMapSettings ms = map->mapSettings( extent, mapSizeMM * dotsPerMM, dpi );
#endif
    QgsRenderContext context; // = QgsRenderContext::fromMapSettings( ms );
    if ( painter )
      context.setPainter( painter );

    context.setFlags( map->layout()->context().renderContextFlags() );
    return context;
  }
}