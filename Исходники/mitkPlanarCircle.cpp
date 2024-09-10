mitk::Point2D mitk::PlanarCircle::ApplyControlPointConstraints(unsigned int index, const Point2D &point)
{
    if ( this->GetPlaneGeometry() ==  nullptr )
    {
        return point;
    }

    Point2D indexPoint;
    this->GetPlaneGeometry()->WorldToIndex( point, indexPoint );

    BoundingBox::BoundsArrayType bounds = this->GetPlaneGeometry()->GetBounds();
    if ( indexPoint[0] < bounds[0] ) {
        indexPoint[0] = bounds[0];
    }
    if ( indexPoint[0] > bounds[1] ) {
        indexPoint[0] = bounds[1];
    }
    if ( indexPoint[1] < bounds[2] ) {
        indexPoint[1] = bounds[2];
    }
    if ( indexPoint[1] > bounds[3] ) {
        indexPoint[1] = bounds[3];
    }

    Point2D constrainedPoint;
    this->GetPlaneGeometry()->IndexToWorld( indexPoint, constrainedPoint );

    if(m_MinMaxRadiusContraintsActive)
    {
        if( index != 0)
        {
            const Point2D &centerPoint = this->GetControlPoint(0);
            double euclideanDinstanceFromCenterToPoint1 = centerPoint.EuclideanDistanceTo(point);

            Vector2D vectorProjectedPoint;
            vectorProjectedPoint = point - centerPoint;
            vectorProjectedPoint.Normalize();

            if( euclideanDinstanceFromCenterToPoint1 > m_MaxRadius )
            {
                vectorProjectedPoint *= m_MaxRadius;
                constrainedPoint = centerPoint;
                constrainedPoint += vectorProjectedPoint;
            }
            else if( euclideanDinstanceFromCenterToPoint1 < m_MinRadius )
            {
                vectorProjectedPoint *= m_MinRadius;
                constrainedPoint = centerPoint;
                constrainedPoint += vectorProjectedPoint;
            }
        }
    }

    return constrainedPoint;
}