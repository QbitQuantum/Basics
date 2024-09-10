// Draw an arc of a great circle between two points on the surface
// of a sphere.
//
// TODO: Currently, we draw constant bearing arcs, as these are easier
// to clip against sphere patch boundaries.
static void
drawGreatCircleArc(const Vector3f& v0, const Vector3f& v1, unsigned int subdivision)
{
#ifndef VESTA_OGLES2
    float d = 1.0f / subdivision;

    glBegin(GL_LINE_STRIP);

    float cosArc = v0.dot(v1);
    float sinArc = sqrt(1.0f - cosArc * cosArc);
    float invSinArc = 1.0f / sinArc;
    float arc = acos(v0.dot(v1));
    float scale = 1.0f + 1.0e-5f;

    Vector3f v = v0 * scale;
    glVertex3fv(v.data());
    for (unsigned int i = 1; i < subdivision; ++i)
    {
        float t = float(i) * d;
        v = ((1.0f - t) * v0 + t * v1).normalized() * scale;
        glVertex3fv(v.data());
    }
    v = v1 * scale;
    glVertex3fv(v.data());
    glEnd();
#endif
}