RNBoolean R3Perpendicular(const R3Vector& vector1, const R3Vector& vector2)
{
    // Normalized vectors ???
    // Return whether vector1 and vector2 are perpendicular
    return RNIsZero(vector1.Dot(vector2));
}