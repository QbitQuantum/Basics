void mitk::PlanarEllipse::GeneratePolyLine()
{
    // clear the PolyLine-Contrainer, it will be reconstructed soon enough...
    this->ClearPolyLines();

    const Point2D &centerPoint = GetControlPoint( 0 );
    const Point2D &boundaryPoint1 = GetControlPoint( 1 );
    const Point2D &boundaryPoint2 = GetControlPoint( 2 );

    Vector2D dir = boundaryPoint1 - centerPoint; dir.Normalize();
    vnl_matrix_fixed<float, 2, 2> rot;

    // differentiate between clockwise and counterclockwise rotation
    int start = 0;
    int end = 64;
    if (dir[1]<0)
    {
        dir[0] = -dir[0];
        start = -32;
        end = 32;
    }
    // construct rotation matrix to align ellipse with control point vector
    rot[0][0] = dir[0];
    rot[1][1] = rot[0][0];
    rot[1][0] = sin(acos(rot[0][0]));
    rot[0][1] = -rot[1][0];

    double radius1 = centerPoint.EuclideanDistanceTo( boundaryPoint1 );
    double radius2 = centerPoint.EuclideanDistanceTo( boundaryPoint2 );

    // Generate poly-line with 64 segments
    for ( int t = start; t < end; ++t )
    {
        double alpha = (double) t * vnl_math::pi / 32.0;

        // construct the new polyline point ...
        vnl_vector_fixed< float, 2 > vec;
        vec[0] = radius1 * cos( alpha );
        vec[1] = radius2 * sin( alpha );
        vec = rot*vec;

        Point2D polyLinePoint;
        polyLinePoint[0] = centerPoint[0] + vec[0];
        polyLinePoint[1] = centerPoint[1] + vec[1];

        // ... and append it to the PolyLine.
        // No extending supported here, so we can set the index of the PolyLineElement to '0'
        AppendPointToPolyLine( 0, PolyLineElement( polyLinePoint, 0 ) );
    }

    AppendPointToPolyLine( 1, PolyLineElement( centerPoint, 0 ) );
    AppendPointToPolyLine( 1, PolyLineElement( GetControlPoint( 3 ), 0 ) );
}