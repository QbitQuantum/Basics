void QgsAnnotationItem::updateBalloon()
{
  //first test if the point is in the frame. In that case we don't need a balloon.
  if ( !mMapPositionFixed ||
       ( mOffsetFromReferencePoint.x() < 0 && ( mOffsetFromReferencePoint.x() + mFrameSize.width() ) > 0
         && mOffsetFromReferencePoint.y() < 0 && ( mOffsetFromReferencePoint.y() + mFrameSize.height() ) > 0 ) )
  {
    mBalloonSegment = -1;
    return;
  }

  //edge list
  QList<QLineF> segmentList;
  segmentList << segment( 0 );
  segmentList << segment( 1 );
  segmentList << segment( 2 );
  segmentList << segment( 3 );

  //find  closest edge / closest edge point
  double minEdgeDist = DBL_MAX;
  int minEdgeIndex = -1;
  QLineF minEdge;
  QgsPoint minEdgePoint;
  QgsPoint origin( 0, 0 );

  for ( int i = 0; i < 4; ++i )
  {
    QLineF currentSegment = segmentList.at( i );
    QgsPoint currentMinDistPoint;
    double currentMinDist = origin.sqrDistToSegment( currentSegment.x1(), currentSegment.y1(), currentSegment.x2(), currentSegment.y2(), currentMinDistPoint );
    if ( currentMinDist < minEdgeDist )
    {
      minEdgeIndex = i;
      minEdgePoint = currentMinDistPoint;
      minEdgeDist = currentMinDist;
      minEdge = currentSegment;
    }
  }

  if ( minEdgeIndex < 0 )
  {
    return;
  }

  //make that configurable for the item
  double segmentPointWidth = 10;

  mBalloonSegment = minEdgeIndex;
  QPointF minEdgeEnd = minEdge.p2();
  mBalloonSegmentPoint1 = QPointF( minEdgePoint.x(), minEdgePoint.y() );
  if ( sqrt( minEdgePoint.sqrDist( minEdgeEnd.x(), minEdgeEnd.y() ) ) < segmentPointWidth )
  {
    mBalloonSegmentPoint1 = pointOnLineWithDistance( minEdge.p2(), minEdge.p1(), segmentPointWidth );
  }

  mBalloonSegmentPoint2 = pointOnLineWithDistance( mBalloonSegmentPoint1, minEdge.p2(), 10 );
}