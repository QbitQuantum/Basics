Vector3f Viewer3D::pos(const Vector3f &p, int x, int y)
{
    float viewport[4] = { };
    glGetFloatv(GL_VIEWPORT, viewport);
    if (changed) calcMatr();

    Vector4f v = Vector4f(p) * matr;
    v.Cartesian();
    float winZ = (1.0f + v.z) * 0.5f;

    v.x = ((float)x - viewport[0]) / viewport[2]*2.0f - 1.0f;
    v.y = ((viewport[3] - (float)y) - viewport[1]) / viewport[3]*2.0f - 1.0f;
    v.z = 2.0f*winZ - 1.0f;
    v.w = 1.0f;
    v *= matr_inv;
    v.Cartesian();
    return Vector3f(v);
}