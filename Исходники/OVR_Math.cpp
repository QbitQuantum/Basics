Matrix4f Matrix4f::LookAtLH(const Vector3f& eye, const Vector3f& at, const Vector3f& up)
{
    Vector3f z = (at - eye).Normalized();  // Forward
    Vector3f x = up.Cross(z).Normalized(); // Right
    Vector3f y = z.Cross(x);

    Matrix4f m(x.x,  x.y,  x.z,  -(x.Dot(eye)),
               y.x,  y.y,  y.z,  -(y.Dot(eye)),
               z.x,  z.y,  z.z,  -(z.Dot(eye)),
               0,    0,    0,    1 ); 
    return m;
}