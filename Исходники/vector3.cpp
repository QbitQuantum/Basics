Vector3 Vector3::cosRandom(const Vector3& normal)
{
    double e1 = G3D::random(0, 1);
    double e2 = G3D::random(0, 1);

    // Angle from normal
    double theta = acos(sqrt(e1));

    // Angle about normal
    double phi   = 2 * G3D_PI * e2;

    // Make a coordinate system
    Vector3 U = normal.direction();
    Vector3 V = Vector3::unitX();

    if (abs(U.dot(V)) > .9)
    {
        V = Vector3::unitY();
    }

    Vector3 W = U.cross(V).direction();
    V = W.cross(U);

    // Convert to rectangular form
    return cos(theta) * U + sin(theta) * (cos(phi) * V + sin(phi) * W);
}