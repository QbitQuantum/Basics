// Assumes rotationOrder is XYZ.
static void
_RotMatToRotTriplet(
    const GfMatrix4d &rotMat,
    GfVec3d *rotTriplet)
{
    GfRotation rot = rotMat.ExtractRotation();
    GfVec3d angles = rot.Decompose(GfVec3d::ZAxis(),
                                   GfVec3d::YAxis(),
                                   GfVec3d::XAxis());
    (*rotTriplet)[0] = angles[2];
    (*rotTriplet)[1] = angles[1];
    (*rotTriplet)[2] = angles[0];
}