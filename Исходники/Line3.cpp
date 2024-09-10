//----------------------------------------------------------------------------
// @ ::DistanceSquared()
// ---------------------------------------------------------------------------
// Returns the distance squared between line and point.
//-----------------------------------------------------------------------------
float DistanceSquared( const Line3& line, const Vector3& point, float& t_c )
{
    Vector3 w = point - line.mOrigin;
    float vsq = line.mDirection.Dot(line.mDirection);
    float proj = w.Dot(line.mDirection);
    t_c = proj/vsq; 

    return w.Dot(w) - t_c*proj;

}   // End of ::DistanceSquared()