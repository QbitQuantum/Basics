osg::Quat FaceTransform::computeQuat(osg::Vec3d direction)
{
    direction.normalize();

    double zAngle = atan2(direction.y(), direction.x());
    osg::Quat zRot(zAngle, osg::Vec3d(0,0,1));

    osg::Vec3d yAxis = zRot * osg::Vec3d(0,1,0);
    double zLength = (direction - osg::Vec3d(0,0,direction.z())).length();
    double yAngle = - atan2(direction.z(), zLength) + osg::PI/2;
    osg::Quat yRot(yAngle, yAxis);

    return zRot * yRot;
}