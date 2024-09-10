QgsGeometry QgsInternalGeometryEngine::taperedBuffer( double start, double end, int segments ) const
{
  start = std::fabs( start );
  end = std::fabs( end );

  auto interpolateWidths = [ start, end ]( const QgsLineString * line )->std::unique_ptr< double [] >
  {
    // ported from JTS VariableWidthBuffer,
    // https://github.com/topobyte/jts/blob/master/jts-lab/src/main/java/com/vividsolutions/jts/operation/buffer/VariableWidthBuffer.java
    std::unique_ptr< double [] > widths( new double[ line->nCoordinates() ] );
    widths[0] = start;
    widths[line->nCoordinates() - 1] = end;

    double lineLength = line->length();
    double currentLength = 0;
    QgsPoint prevPoint = line->pointN( 0 );
    for ( int i = 1; i < line->nCoordinates() - 1; ++i )
    {
      QgsPoint point = line->pointN( i );
      double segmentLength = point.distance( prevPoint );
      currentLength += segmentLength;
      double lengthFraction = lineLength > 0 ? currentLength / lineLength : 1;
      double delta = lengthFraction * ( end - start );
      widths[i] = start + delta;
      prevPoint = point;
    }
    return widths;
  };

  return variableWidthBuffer( segments, interpolateWidths );
}