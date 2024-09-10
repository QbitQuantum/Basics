MPI_Point2D MPI_ParticleStroke::linearPositionToPoint( float position ) const
{

    // go from a linear position along the stroke in canonical coordinates
    // (where breakpoints corresponsd to successive integer coords) to
    // 2d space coordinates.  linearly interpolate between breakpoints
    // for fractional positions.
    // assumes 0.0 <= position <= pointList_.size()-1

    // if it's the last index, return the last point
    // otherwise, interpolate between current point and the next one

    float integerpart;
    float fractionalpart = modff( position, &integerpart );
    unsigned int firstindex = static_cast<unsigned int>( integerpart );
    unsigned int secondindex = static_cast<unsigned int>( integerpart+1.0 );

    // if we're after the last point, just return it
    if ( firstindex == pointList_.size()-1 )
        return pointList_[firstindex]->getPoint();

    // interpolate between the first and second points
    MPI_Point2D const& firstpoint = pointList_[firstindex]->getPoint();
    MPI_Point2D const& secondpoint = pointList_[secondindex]->getPoint();
    return MPI_Point2D(
            (1.0-fractionalpart)*firstpoint.getX() + fractionalpart*secondpoint.getX(),
            (1.0-fractionalpart)*firstpoint.getY() + fractionalpart*secondpoint.getY() );

}