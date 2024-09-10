void R3Matrix::Rotate(const R3Vector& from, const R3Vector& to)
{
    // rotate matrix that takes direction of vector "from" -> "to"
    // This is a quickie hack -- there's got to be a better way
    double d1 = from.Length();
    if (d1 == 0) return;
    double d2 = to.Length();
    if (d2 == 0) return;
    double cosine = from.Dot(to) / (d1 * d2);
    double radians = acos(cosine);
    R3Vector axis = from % to;
    axis.Normalize();
    Rotate(axis, radians);
}