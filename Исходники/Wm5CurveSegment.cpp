//----------------------------------------------------------------------------
float CurveSegment::Torsion (float u) const
{
    AVector velocity = PU(u);
    AVector acceleration = PUU(u);
    AVector cross = velocity.Cross(acceleration);
    float denom = cross.SquaredLength();

    if (denom >= Mathf::ZERO_TOLERANCE)
    {
        AVector jerk = PUUU(u);
        float numer = cross.Dot(jerk);
        return numer/denom;
    }
    else
    {
        // Torsion is indeterminate, just return 0.
        return 0.0f;
    }
}