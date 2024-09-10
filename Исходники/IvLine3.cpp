//----------------------------------------------------------------------------
// @ IvLine3::ClosestPoint()
// ---------------------------------------------------------------------------
// Returns the closest point on line to point.
//-----------------------------------------------------------------------------
IvVector3 IvLine3::ClosestPoint(const IvVector3& point) const
{
    IvVector3 w = point - mOrigin;
    float vsq = mDirection.Dot(mDirection);
    float proj = w.Dot(mDirection);

    return mOrigin + (proj/vsq)*mDirection;

}   // End of IvLine3::ClosestPoint()