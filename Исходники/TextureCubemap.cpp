void TextureCubemap::getCubeVector(unsigned int size, unsigned int index, unsigned int x, unsigned int y, Vec3& v) const
{
    auto s = (float(x) + 0.5f) / float(size);
    auto t = (float(y) + 0.5f) / float(size);
    auto sc = s * 2.0f - 1.0f;
    auto tc = t * 2.0f - 1.0f;

    if (index == 0)
        v.setXYZ(1.0f, -tc, -sc);
    else if (index == 1)
        v.setXYZ(-1.0f, -tc, sc);
    else if (index == 2)
        v.setXYZ(sc, 1.0f, tc);
    else if (index == 3)
        v.setXYZ(sc, -1.0f, -tc);
    else if (index == 4)
        v.setXYZ(sc, -tc, 1.0f);
    else if (index == 5)
        v.setXYZ(-sc, -tc, -1.0f);

    v.normalize();
}