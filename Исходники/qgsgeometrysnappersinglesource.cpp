static bool snapLineString( QgsLineString *linestring, QgsSpatialIndex &index, QVector<AnchorPoint> &pnts, double thresh )
{
  QVector<QgsPoint> newPoints;
  QVector<int> anchors;  // indexes of anchors for vertices
  double thresh2 = thresh * thresh;
  double minDistX, minDistY;   // coordinates of the closest point on the segment line
  bool changed = false;

  // snap vertices
  for ( int v = 0; v < linestring->numPoints(); v++ )
  {
    double x = linestring->xAt( v );
    double y = linestring->yAt( v );
    QgsRectangle rect( x, y, x, y );

    // Find point ( should always find one point )
    QList<QgsFeatureId> fids = index.intersects( rect );
    Q_ASSERT( fids.count() == 1 );

    int spoint = fids.first();
    int anchor = pnts[spoint].anchor;
    if ( anchor >= 0 )
    {
      // to be snapped
      linestring->setXAt( v, pnts[anchor].x );
      linestring->setYAt( v, pnts[anchor].y );
      anchors.append( anchor ); // point on new location
      changed = true;
    }
    else
    {
      anchors.append( spoint ); // old point
    }
  }

  // Snap all segments to anchors in threshold
  for ( int v = 0; v < linestring->numPoints() - 1; v++ )
  {
    double x1 = linestring->xAt( v );
    double x2 = linestring->xAt( v + 1 );
    double y1 = linestring->yAt( v );
    double y2 = linestring->yAt( v + 1 );

    newPoints << linestring->pointN( v );

    // Box
    double xmin = x1, xmax = x2, ymin = y1, ymax = y2;
    if ( xmin > xmax )
      std::swap( xmin, xmax );
    if ( ymin > ymax )
      std::swap( ymin, ymax );

    QgsRectangle rect( xmin - thresh, ymin - thresh, xmax + thresh, ymax + thresh );

    // Find points
    const QList<QgsFeatureId> fids = index.intersects( rect );

    QVector<AnchorAlongSegment> newVerticesAlongSegment;

    // Snap to anchor in threshold different from end points
    for ( QgsFeatureId fid : fids )
    {
      int spoint = fid;

      if ( spoint == anchors[v] || spoint == anchors[v + 1] )
        continue; // end point
      if ( pnts[spoint].anchor >= 0 )
        continue; // point is not anchor

      // Check the distance
      double dist2 = QgsGeometryUtils::sqrDistToLine( pnts[spoint].x, pnts[spoint].y, x1, y1, x2, y2, minDistX, minDistY, 0 );
      // skip points that are behind segment's endpoints or extremely close to them
      double dx1 = minDistX - x1, dx2 = minDistX - x2;
      double dy1 = minDistY - y1, dy2 = minDistY - y2;
      bool isOnSegment = !qgsDoubleNear( dx1 * dx1 + dy1 * dy1, 0 ) && !qgsDoubleNear( dx2 * dx2 + dy2 * dy2, 0 );
      if ( isOnSegment && dist2 <= thresh2 )
      {
        // an anchor is in the threshold
        AnchorAlongSegment item;
        item.anchor = spoint;
        item.along = QgsPointXY( x1, y1 ).distance( minDistX, minDistY );
        newVerticesAlongSegment << item;
      }
    }

    if ( !newVerticesAlongSegment.isEmpty() )
    {
      // sort by distance along the segment
      std::sort( newVerticesAlongSegment.begin(), newVerticesAlongSegment.end(), []( const AnchorAlongSegment & p1, const AnchorAlongSegment & p2 )
      {
        return ( p1.along < p2.along ? -1 : ( p1.along > p2.along ) );
      } );

      // insert new vertices
      for ( int i = 0; i < newVerticesAlongSegment.count(); i++ )
      {
        int anchor = newVerticesAlongSegment[i].anchor;
        newPoints << QgsPoint( pnts[anchor].x, pnts[anchor].y, 0 );
      }
      changed = true;
    }
  }

  // append end point
  newPoints << linestring->pointN( linestring->numPoints() - 1 );

  // replace linestring's points
  if ( changed )
    linestring->setPoints( newPoints );

  return changed;
}