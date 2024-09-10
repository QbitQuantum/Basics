void R4Matrix:: 
Rotate(const R3Vector& from, const R3Vector& to)
{
    // rotate matrix that takes direction of vector "from" -> "to"
    // This is a quickie hack -- there's got to be a better way
    RNAngle radians = R3InteriorAngle(from, to);
    R3Vector axis = from % to;
    axis.Normalize();
    Rotate(axis, radians);
}