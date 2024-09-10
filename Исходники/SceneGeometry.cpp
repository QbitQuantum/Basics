double SceneGeometry::getOPShadowAngle() const
{
    const Vector3 planeZ = getOPZVector();
    const Vector3 groundShadow = planeZ - (mXs / mXs.dot(planeZ));
    const double scale = groundShadow.dot(planeZ) / mZs.dot(planeZ);
    return getOPAngle(groundShadow - mZs * scale);
}