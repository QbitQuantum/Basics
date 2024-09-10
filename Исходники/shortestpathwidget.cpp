void RgShortestPathWidget::exportPath()
{
  RgExportDlg dlg( this );
  if ( !dlg.exec() )
    return;

  QgsVectorLayer *vl = dlg.mapLayer();
  if ( vl == NULL )
    return;

  QgsPoint p1, p2;
  QgsGraph *path = getPath( p1, p2 );
  if ( path == NULL )
    return;

  QgsCoordinateTransform ct( mPlugin->iface()->mapCanvas()->mapRenderer()->destinationCrs(),
                             vl->crs() );

  int startVertexIdx = path->findVertex( p1 );
  int stopVertexIdx  = path->findVertex( p2 );

  QgsPolyline p;
  while ( startVertexIdx != stopVertexIdx )
  {
    QgsGraphArcIdList l = path->vertex( stopVertexIdx ).inArc();
    if ( l.empty() )
      break;
    const QgsGraphArc& e = path->arc( l.front() );
    p.push_front( ct.transform( path->vertex( e.inVertex() ).point() ) );
    stopVertexIdx = e.outVertex();
  }
  p.push_front( ct.transform( p1 ) );

  vl->startEditing();
  QgsFeature f;
  f.setGeometry( QgsGeometry::fromPolyline( p ) );
  vl->addFeature( f );
  vl->updateExtents();

  mPlugin->iface()->mapCanvas()->update();
  delete path;
}