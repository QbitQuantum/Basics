void Galaxy::renderGalaxyEllipsoid(const GLContext& context,
                                   const Vec3f& offset,
                                   const Quatf&,
                                   float,
                                   float pixelSize)
{
    float discSizeInPixels = pixelSize * getRadius() / offset.length();
    unsigned int nRings = (unsigned int) (discSizeInPixels / 4.0f);
    unsigned int nSlices = (unsigned int) (discSizeInPixels / 4.0f);
    nRings = max(nRings, 100u);
    nSlices = max(nSlices, 100u);

    VertexProcessor* vproc = context.getVertexProcessor();
    if (vproc == NULL)
        return;

    //int e = min(max((int) type - (int) E0, 0), 7);
    Vec3f scale = Vec3f(1.0f, 0.9f, 1.0f) * getRadius();
    Vec3f eyePos_obj = -offset * (~getOrientation()).toMatrix3();

    vproc->enable();
    vproc->use(vp::ellipticalGalaxy);

    vproc->parameter(vp::EyePosition, eyePos_obj);
    vproc->parameter(vp::Scale, scale);
    vproc->parameter(vp::InverseScale,
                     Vec3f(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z));
    vproc->parameter((vp::Parameter) 23, eyePos_obj.length() / scale.x, 0.0f, 0.0f, 0.0f);

    glRotate(getOrientation());

    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    for (unsigned int i = 0; i < nRings; i++)
    {
        float phi0 = (float) PI * ((float) i / (float) nRings - 0.5f);
        float phi1 = (float) PI * ((float) (i + 1) / (float) nRings - 0.5f);

        glBegin(GL_QUAD_STRIP);
        for (unsigned int j = 0; j <= nSlices; j++)
        {
            float theta = (float) (PI * 2) * (float) j / (float) nSlices;
            float sinTheta = (float) sin(theta);
            float cosTheta = (float) cos(theta);

            glVertex3f((float) cos(phi0) * cosTheta * scale.x,
                       (float) sin(phi0)            * scale.y,
                       (float) cos(phi0) * sinTheta * scale.z);
            glVertex3f((float) cos(phi1) * cosTheta * scale.x,
                       (float) sin(phi1)            * scale.y,
                       (float) cos(phi1) * sinTheta * scale.z);
        }
        glEnd();
    }
    glEnable(GL_TEXTURE_2D);

    vproc->disable();
}