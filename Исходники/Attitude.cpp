float Attitude::getDip() const
{

    Vector2f north = Vector2f::UnitX(); // parallel to x axis
    Vector2f dip = getDipDirectionVector().head(
        2); // he third element is 0 (working on horizontal plane)

    float angle = acos(north.dot(dip)) * 180 / M_PI;

    if (dip(1)
        > 0.0) // if y component is postive we are in the 180 to 360 half-space
        angle = 360 - angle;

    return angle;
}