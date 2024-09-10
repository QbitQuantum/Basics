static void gramSchmidt(Vec3f &a, Vec3f &b, Vec3f &c)
{
    a.normalize();
    b -= a*a.dot(b);
    if (b.lengthSq() < 1e-5)
        b = randomOrtho(a);
    else
        b.normalize();

    c -= a*a.dot(c);
    c -= b*b.dot(c);
    if (c.lengthSq() < 1e-5)
        c = a.cross(b);
    else
        c.normalize();
}