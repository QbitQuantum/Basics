static void longLatLabel(const string& labelText,
                         double longitude,
                         double latitude,
                         const Vector3d& viewRayOrigin,
                         const Vector3d& viewNormal,
                         const Vector3d& bodyCenter,
                         const Quaterniond& bodyOrientation,
                         const Vector3f& semiAxes,
                         float labelOffset,
                         Renderer* renderer)
{
    double theta = degToRad(longitude);
    double phi = degToRad(latitude);
    Vector3d pos(cos(phi) * cos(theta) * semiAxes.x(),
                 sin(phi) * semiAxes.y(),
                 -cos(phi) * sin(theta) * semiAxes.z());

    float nearDist = renderer->getNearPlaneDistance();

    pos = pos * (1.0 + labelOffset);

    double boundingRadius = semiAxes.maxCoeff();

    // Draw the label only if it isn't obscured by the body ellipsoid
    double t = 0.0;
    if (testIntersection(Ray3d(viewRayOrigin, pos - viewRayOrigin), Ellipsoidd(semiAxes.cast<double>()), t) && t >= 1.0)
    {
        // Compute the position of the label
        Vector3d labelPos = bodyCenter +
                            bodyOrientation.conjugate() * pos * (1.0 + labelOffset);

        // Calculate the intersection of the eye-to-label ray with the plane perpendicular to
        // the view normal that touches the front of the objects bounding sphere
        double planetZ = viewNormal.dot(bodyCenter) - boundingRadius;
        if (planetZ < -nearDist * 1.001)
            planetZ = -nearDist * 1.001;
        double z = viewNormal.dot(labelPos);
        labelPos *= planetZ / z;

        renderer->addObjectAnnotation(NULL, labelText,
                                      Renderer::PlanetographicGridLabelColor,
                                      labelPos.cast<float>());
    }
}