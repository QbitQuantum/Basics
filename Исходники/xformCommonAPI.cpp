// Assumes rotationOrder is XYZ.
static void
_RotMatToRotXYZ(
    const GfMatrix4d &rotMat,
    GfVec3f *rotXYZ)
{
    GfRotation rot = rotMat.ExtractRotation();
    GfVec3d angles = rot.Decompose(GfVec3d::ZAxis(),
                                   GfVec3d::YAxis(),
                                   GfVec3d::XAxis());
    *rotXYZ = GfVec3f(angles[2], angles[1], angles[0]);
}