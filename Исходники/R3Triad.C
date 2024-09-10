void R3Triad::
Rotate(const R3Vector& from, const R3Vector& to)
{
    // Rotate each axis
    RNAngle angle = R3InteriorAngle(from, to);
    R3Vector rotaxis = from % to;
    rotaxis.Normalize();
    Rotate(rotaxis, angle);
}