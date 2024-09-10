double SinValue(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    Vector3D ba = b-a;
    Vector3D ca = c-a;
    Vector3D t= ba.cross(ca);
    return t.norm()/(ba.norm()*ca.norm());
}