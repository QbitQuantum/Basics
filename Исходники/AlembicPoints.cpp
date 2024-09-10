// static
void AlembicPoints::ConvertMaxEulerXYZToAlembicQuat(const Point3 &degrees, Abc::Quatd &quat)
{
    // Get the angles as a float vector of radians - strangeley they already are even though the documentation says degrees
    float angles[] = { degrees.x, degrees.y, degrees.z };

    // Convert the angles to a quaternion
    Quat maxQuat;
    EulerToQuat(angles, maxQuat, EULERTYPE_XYZ);

    // Convert the quaternion to an angle and axis
    maxQuat.Normalize();
    AngAxis maxAngAxis(maxQuat);

    ConvertMaxAngAxisToAlembicQuat(maxAngAxis, quat);
}