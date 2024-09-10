//=============================================================================
Point2F Ray2::getPoint(double parameter, double offset) const
{
    Vector2F delta = dir_;
    delta.multiply(parameter);
    Point2F result =  origin_;
    result.add(delta);

    if (offset == 0.0) return result;

    Vector2F offsetVec = dir_;
    offsetVec.setPerpendLeft();
    offsetVec.multiply( offset/offsetVec.getLength() );
    result.add(offsetVec);

    return result;
}